# AutoPerception

A C++ perception system that models the core of autonomous-vehicle sensing: multiple sensors reporting obstacles, fused into a single clean picture of the world, then classified by type. Every algorithm from the computer-vision geometry to the machine-learning classifier is implemented from scratch to demonstrate the underlying engineering rather than wrap a black box.

## Overview

AutoPerception simulates how a self-driving car turns raw sensor output into an actionable, labeled list of obstacles. A central `PerceptionSystem` owns a set of sensors, collects what each one detects, removes duplicate detections with the Non-Maximum Suppression (NMS) algorithm, and reports the result ordered by distance from the vehicle. On top of that perception core, a from-scratch machine-learning pipeline classifies each detection's object type from the geometry of its bounding box. It is built as a learning and portfolio project around modern C++, computer-vision fundamentals, and supervised-learning methodology.

## What it demonstrates

- **Modern C++17** — `std::unique_ptr` and RAII for automatic, leak-free ownership of sensors; value semantics; and standard-library containers and algorithms
- **Polymorphism** — an abstract `Sensor` base class with `Lidar`, `Camera`, and `Radar` implementations used through a single interface
- **Computer-vision algorithms from scratch** — axis-aligned bounding boxes, Intersection-over-Union, and non-maximum suppression, with no third-party CV dependency
- **Machine learning from scratch** — a k-nearest-neighbors classifier, feature standardization, and a reproducible train/test split, with no ML libraries
- **Sound ML methodology** — held-out evaluation, training-only feature scaling to prevent data leakage, and a confusion matrix for per-class diagnosis
- **A real build and test setup** — a CMake project split into a library, an application, and a CTest-driven unit-test suite

## Features

- Multiple sensor types (lidar, camera, radar) reporting detections through a common interface
- A perception system that fuses detections, sorts them by distance, and finds the nearest obstacle
- Bounding-box geometry with Intersection-over-Union overlap scoring
- Non-maximum suppression to collapse overlapping detections down to one box per object
- Synthetic labeled-dataset generation with per-class geometry and Gaussian noise
- A CSV-backed data pipeline: write detections to disk, load them back as feature vectors
- Feature standardization fitted on training data only, with held-out evaluation
- A from-scratch k-nearest-neighbors classifier reporting accuracy and a confusion matrix
- A unit-test suite covering the geometry and suppression logic

## Computer vision capability

The detection-processing core is built from three composable pieces:

- **`BoundingBox`** — an axis-aligned rectangle (top-left corner plus width and height) describing where a detection sits in the frame.
- **`iou(a, b)`** — Intersection-over-Union, the overlap between two boxes on a 0–1 scale: `0` for disjoint boxes, `1` for identical ones. It is the metric for deciding whether two boxes describe the same object.
- **`nonMaxSuppression(detections, threshold)`** — given a cluster of overlapping detections, keeps the highest-confidence box and discards any box overlapping it by more than the threshold, leaving one detection per object.

## Machine learning capability

Building on the computer-vision core, AutoPerception turns its detections into a supervised-learning problem: classify each detection's object type (pedestrian, car, truck) from the geometry of its bounding box. The entire pipeline is implemented from scratch — no scikit-learn, no ML frameworks — to demonstrate the mechanics of a model and, just as importantly, the methodology of evaluating one honestly.

The pipeline is built from composable stages, each in its own module:

- **`generateDataset(samplesPerClass, seed)`** — synthesizes a labeled dataset with separable classes. Each class has characteristic box dimensions drawn from a Gaussian, so samples vary realistically while the classes remain distinguishable. A fixed seed makes the dataset reproducible.
- **`writeDetections(...)` / `loadDataset(...)`** — persist detections to a CSV on disk and read them back into in-memory feature vectors, mirroring how a real pipeline separates data storage from model training. Each detection becomes a row of features (`width, height, aspect_ratio, area, confidence`) plus a label.
- **`trainTestSplit(samples, fraction, seed)`** — shuffles the data, so each split contains a mix of all classes rather than being ordered by label, then partitions it into a training set and a held-out test set.
- **`Scaler`** — standardizes each feature to mean 0 and unit variance. It learns the mean and standard deviation from the **training set only**, then applies those same parameters to the test set, so no test-set information leaks into the scaling. This step is essential for k-NN: without it, large-magnitude features (area, in the thousands) would dominate the distance metric and drown out the most discriminative feature (aspect ratio, near 1).
- **`KNN`** — a k-nearest-neighbors classifier. It predicts a detection's class by finding the *k* closest training examples in feature space and taking a majority vote. It reports accuracy on the held-out test set and prints a confusion matrix showing which classes get confused.

### Methodology and results

On the synthetic dataset, the classifier reaches very high test accuracy (100% on a well-separated dataset). That number is **expected, not impressive on its own** — the classes are designed to occupy distinct regions of feature space, so a correct pipeline should separate them cleanly. The value of this capability is not the headline accuracy but the engineering around it:

- **Honest evaluation** — accuracy is measured only on data the model never saw during training, avoiding the inflated scores that come from testing on training data.
- **No data leakage** — feature-scaling parameters are learned from the training set alone and applied to the test set, the way they would be in production where test data is genuinely unseen.
- **Diagnosability** — the confusion matrix reveals not just *how many* errors but *which* classes are mistaken for which, the information needed to actually improve a model.

Class separation is a tunable property of the data generator: increasing the per-class noise causes the classes to overlap and accuracy to fall, demonstrating that the pipeline responds to genuine problem difficulty rather than producing a fixed result.

## Project structure

```
AutoPerception/
├── include/        # headers:
│                   #   Perception: Vec2, Sensor + Lidar/Camera/Radar, Detection,
│                   #               BoundingBox, Geometry (IoU), Nms, PerceptionSystem
│                   #   ML pipeline: DatasetLogger, DataGenerator, Dataset,
│                   #               Split, Scaler, KNN
├── src/            # implementations and main.cpp
├── tests/          # unit tests run by CTest
├── CMakeLists.txt  # builds a library, the application, and the tests
└── README.md
```

The project's logic lives in a `perception` library. The application and the test suite are thin executables that both link against it, so the same code backs what ships and what is tested.

## Building

Requirements: a C++17 compiler and CMake 3.16 or newer.

```
git clone https://github.com/Heladio-C/autoperception.git
cd autoperception
cmake -B build
cmake --build build
```

## Running

```
./build/autoperception
```

On Windows with a Visual Studio generator, the binary is at `build/Debug/autoperception.exe`.

Running the application performs the computer-vision demo (sensors → detections → NMS), then runs the full machine-learning pipeline (generate → load → split → scale → train → evaluate) and prints the test accuracy and confusion matrix.

## Tests

```
ctest --test-dir build --output-on-failure
```

On multi-configuration generators such as Visual Studio, add the configuration flag:

```
ctest --test-dir build -C Debug --output-on-failure
```

## Roadmap

Capabilities planned on top of the current pipeline:

- Object tracking across frames (Kalman filtering)
- Path planning around detected obstacles (A*)
- A second classifier (logistic regression) to compare against k-NN on the same dataset
