#include "PerceptionSystem.h"
#include "Lidar.h"
#include "Camera.h"
#include "Radar.h"
#include "Vec2.h"
#include "Detection.h"
#include "PerceptionError.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main(){

    try{
    PerceptionSystem perception;
    perception.addSensor(new Lidar("FrontLidar", Vec2(2.5, 0.0), 80.0));
    perception.addDetection({Vec2(10.0, 3.0), "car"});
    perception.addDetection({Vec2(4.0, -1.0), "pedestrian"});

    const Detection& closest = perception.nearest();
    cout << "Nearest: " << closest.type << "at" << closest.position << endl;
    }
    catch(const exception& e){
        cout << "Error: " << e.what() << endl;
    } 

    // Case 2: querying an empty system -> PerceptionError
    try {
        PerceptionSystem empty;
        const Detection& d = empty.nearest();   // throws here
        cout << d.type << endl;                  // never runs
    }
    catch (const PerceptionError& e) {
        cout << "Caught PerceptionError: " << e.what() << endl;
    }


    //case 3: builiding invalid sensor with invalid arguments
    try {
        Lidar bad("BrokenLidar", Vec2(0, 0), -5.0);   // throws in constructor
        bad.scan();                                    // never runs
    }
    catch (const invalid_argument& e) {
        cout << "Caught invalid_argument: " << e.what() << endl;
    }

    // Case 4: one handler catching the whole std::exception family
    try {
        Camera bad("BrokenCam", Vec2(0, 0), 400.0);   // FOV > 360 -> throws
    }
    catch (const exception& e) {                       // base-class catch
        cout << "Caught (as std::exception): " << e.what() << endl;
    }

    cout << "Program finished normally (no crash)." << endl;


    return 0;
}