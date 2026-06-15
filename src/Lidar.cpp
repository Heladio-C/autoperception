#include "Lidar.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Lidar::Lidar(const string& name, const Vec2& position, double range) : Sensor(name, position), range(range) {

    if(range <= 0.0){
        throw invalid_argument("Lidar range must be positive (got " + to_string(range) + ")");
    }

}


double Lidar::getRange() const {
    return range;
}

void Lidar::scan() const {
    cout << name << " sweeping lasers out to " << range << "m..." << endl;
}