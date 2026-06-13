#include "Sensor.h"
#include "Lidar.h"
#include "Camera.h"
#include "Radar.h"
#include "Vec2.h"
#include <iostream>
using namespace std;

int main(){
    //
    Sensor* sensors[3];
    sensors[0] = new Lidar("FrontLidar", Vec2(2.5, 0.0), 80.0);
    sensors[1] = new Camera("FrontCam", Vec2(2.0, 0.5), 90.0);
    sensors[2] = new Radar("RearRadar", Vec2(-1.5, 0.0), 60.0);
    
    for(int i = 0; i < 3; i++){
       sensors[i] -> printInfo();
       sensors[i] -> scan();
    }

    cout << "\nLive sensors: " << Sensor::getCount() << endl;

    for(int i = 0; i < 3; i++){
        delete sensors[i];
    }
    return 0;
}