# AutoPerception

A C++ perception system that models the core of an autonomous-vehicle sensing pipeline — multiple sensors reporting obstacles, fused into a single clean picture of the world. Every algorithm is implemented from scratch, with no OpenCV or external computer-vision libraries, to demonstrate the underlying engineering rather than wrap a black box.

## Overview

AutoPerception simulates how a self-driving car turns raw sensor output into an actionable list of obstacles. A central `PerceptionSystem` owns a set of sensors, collects what each one detects, removes duplicate detections, and reports the result ordered by distance from the vehicle. It is built as a learning and portfolio project around modern C++ and computer-vision fundamentals.

## What it demonstrates

- **Modern C++17** — `std::unique_ptr` and RAII for automatic, leak-free ownership of sensors; value semantics; and standard-library containers and algorithms
- **Polymorphism** — an abstract `Sensor` base class with `Lidar`, `Camera`, and `Radar` implementations used through a single interface
- **Computer-vision algorithms from scratch** — axis-aligned bounding boxes, Intersection-over-Union, and non-maximum suppression, with no third-party CV dependency
- **A real build and test setup** — a CMake project split into a library, an application, and a CTest-driven unit-test suite

## Features

- Multiple sensor types (lidar, camera, radar) reporting detections through a common interface
- A perception system that fuses detections, sorts them by distance, and finds the nearest obstacle
- Bounding-box geometry with Intersection-over-Union overlap scoring
- Non-maximum suppression to collapse overlapping detections down to one box per object
- A unit-test suite covering the geometry and suppression logic

## Computer vision capability

The detection-processing core is built from three composable pieces:

- **`BoundingBox`** — an axis-aligned rectangle (top-left corner plus width and height) describing where a detection sits in the frame.
- **`iou(a, b)`** — Intersection-over-Union, the overlap between two boxes on a 0–1 scale: `0` for disjoint boxes, `1` for identical ones. It is the metric for deciding whether two boxes describe the same object.
- **`nonMaxSuppression(detections, threshold)`** — given a cluster of overlapping detections, keeps the highest-confidence box and discards any box overlapping it by more than the threshold, leaving one detection per object.

## Project structure

```
AutoPerception/
├── include/        # headers: Vec2, Sensor + Lidar/Camera/Radar, Detection,
│                   #          BoundingBox, Geometry (IoU), Nms, PerceptionSystem
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
cd AutoPerception
cmake -B build
cmake --build build
```

## Running

```
./build/autoperception
```

On Windows with a Visual Studio generator, the binary is at `build/Debug/autoperception.exe`.

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
- A data pipeline for loading and replaying recorded scenarios
