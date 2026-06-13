#include "Lidar.h"
#include <iostream>
using namespace std;

Lidar::Lidar(const string& name, const Vec2& position, double range) : Sensor(name, position), range(range) {}


double Lidar::getRange() const {
    return range;
}

void Lidar::scan() const {
    cout << name << " sweeping lasers out to " << range << "m..." << endl;
}