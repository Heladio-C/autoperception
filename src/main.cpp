#include "PerceptionSystem.h"
#include "BoundingBox.h"
#include "Lidar.h"
#include "Camera.h"
#include "Radar.h"
#include "Vec2.h"
#include "Detection.h"
#include <iostream>
#include <memory>
using namespace std;

int main(){


    BoundingBox box{10.0, 20.0, 30.0, 40.0};

    cout << "Area=" << box.area();
    
    PerceptionSystem perception;
    perception.addSensor(make_unique<Lidar>("FrontLidar", Vec2(2.5, 0.0), 80.0));
    perception.addSensor(make_unique<Camera>("FrontCam", Vec2(2.0, 0.5), 90.0));
    perception.addSensor(make_unique<Radar>("RearRadar", Vec2(-1.5, 0.0), 60.0));

    perception.addDetection({Vec2(25.0, 8.0), "truck"});
    perception.addDetection({Vec2(10.0, 3.0), "car"});
    perception.addDetection({Vec2(4.0, -1.0), "pedestrian"});

    perception.runScan();

    perception.sortByDistance();
    cout << "Detections (Closest first):" << endl;
    perception.report();

    const Detection& closest = perception.nearest();
    cout << "\nMost urgent: " << closest.type << " at " << closest.position << " (" << closest.position.magnitude() << " m)" << endl;



    return 0;
}