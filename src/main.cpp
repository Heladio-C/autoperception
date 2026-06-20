#include "PerceptionSystem.h"
#include "BoundingBox.h"
#include "Lidar.h"
#include "Camera.h"
#include "Radar.h"
#include "Vec2.h"
#include "Detection.h"
#include "DatasetLogger.h"
#include "DataGenerator.h"
#include "Dataset.h"
#include "Split.h"
#include "Scaler.h"
#include "KNN.h"

#include <vector>
#include <iostream>
#include <memory>
using namespace std;

// Computer-vision demo: sensors produce detections, then non-maximum
// suppression collapses overlapping boxes down to one per object.
void runPerceptionDemo() {
    PerceptionSystem perception;
    perception.addSensor(make_unique<Lidar>("FrontLidar", Vec2(2.5, 0.0), 80.0));
    perception.addSensor(make_unique<Camera>("FrontCam", Vec2(2.0, 0.5), 90.0));
    perception.addSensor(make_unique<Radar>("RearRadar", Vec2(-1.5, 0.0), 60.0));

    perception.addDetection({ Vec2(10, 3), "car",   BoundingBox{100, 100, 50, 40}, 0.92 });
    perception.addDetection({ Vec2(10, 3), "car",   BoundingBox{104, 102, 50, 40}, 0.75 });
    perception.addDetection({ Vec2(25, 8), "truck", BoundingBox{300, 200, 50, 40}, 0.88 });

    cout << "Before NMS:\n";
    perception.report();

    perception.cleanDetections();

    cout << "\nAfter NMS:\n";
    perception.report();
}

// Machine-learning pipeline, end to end: generate a labeled dataset, persist
// and reload it, split into train/test, standardize features, then train and
// evaluate a k-NN classifier.
void runMLPipeline() {
    // 1. Generate a synthetic labeled dataset and write it to CSV.
    vector<Detection> trainingSet = generateDataset(200);   // 200 samples per class
    writeDetections(trainingSet, "dataset.csv");

    // 2. Load it back into feature vectors.
    vector<Sample> data = loadDataset("dataset.csv");
    cout << "Loaded " << data.size() << " samples from dataset.csv\n";

    // 3. Split into training and held-out test sets (80/20).
    SplitData split = trainTestSplit(data, 0.8);
    cout << "Train: " << split.trainingSet.size()
         << "  |  Test: " << split.testSet.size() << "\n";

    // 4. Standardize features — fit on TRAIN only, then apply to both.
    Scaler scaler;
    scaler.fit(split.trainingSet);
    vector<Sample> trainScaled = scaler.transform(split.trainingSet);
    vector<Sample> testScaled  = scaler.transform(split.testSet);

    // 5. Train k-NN and evaluate on the held-out test set.
    KNN model(5);
    model.fit(trainScaled);
    double accuracy = model.evaluate(testScaled);
    cout << "\nk-NN test accuracy: " << (accuracy * 100.0) << "%\n";

    // 6. Show which classes get confused.
    model.confusionMatrix(testScaled);
}

int main() {
    runPerceptionDemo();

    cout << "\n========================================\n\n";

    runMLPipeline();

    return 0;
}