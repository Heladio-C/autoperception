#include "PerceptionSystem.h"
#include "Geometry.h"
#include "BoundingBox.h"
#include "Lidar.h"
#include "Camera.h"
#include "Radar.h"
#include "Vec2.h"
#include "Detection.h"
#include "Nms.h"
#include "DatasetLogger.h"
#include "DataGenerator.h"
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

int main(){

    PerceptionSystem perception;
    perception.addSensor(make_unique<Lidar>("FrontLidar", Vec2(2.5, 0.0), 80.0));
    perception.addSensor(make_unique<Camera>("FrontCam", Vec2(2.0, 0.5), 90.0));
    perception.addSensor(make_unique<Radar>("RearRadar", Vec2(-1.5, 0.0), 60.0));


    perception.addDetection({ Vec2(10, 3), "car",   BoundingBox{100, 100, 50, 40}, 0.92 });
    perception.addDetection({ Vec2(10, 3), "car",   BoundingBox{104, 102, 50, 40}, 0.75 });
    perception.addDetection({ Vec2(25, 8), "truck", BoundingBox{300, 200, 50, 40}, 0.88 });

    std::cout << "Before NMS:\n";
    perception.report();

    perception.cleanDetections();

    std::cout << "\nAfter NMS:\n";
    perception.report();

    //generator dataset and write to file
    std::vector<Detection> trainingSet = generateDataset(200); //generate 200 samples per class
    writeDetections(trainingSet, "dataset.csv");
    std::cout << "\nGenerated dataset with " << trainingSet.size() << " samples and saved to dataset.csv\n";
    return 0;
}