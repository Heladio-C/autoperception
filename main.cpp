#include "PerceptionSystem.h"
#include "Lidar.h"
#include "Camera.h"
#include "Radar.h"
#include "Vec2.h"
#include "Detection.h"
#include <iostream>
using namespace std;

int main(){
    PerceptionSystem perception;

    perception.addSensor(new Lidar("FrontLidar", Vec2(2.5, 0.0), 80.0));
    perception.addSensor(new Camera("FrontCam", Vec2(2.0, 0.5), 90.0));
    perception.addSensor(new Radar("RearRadar", Vec2(-1.5, 0.0), 60.0));

    perception.addDetection({Vec2(10.0, 3.0), "car"});
    perception.addDetection({Vec2(4.0, -1.0), "pedestrian"});
    perception.addDetection({Vec2(25.0, 8.0), "truck"});

    perception.runScan();
    perception.report();


    return 0;
}