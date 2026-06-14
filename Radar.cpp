#include "Radar.h"
#include <iostream>
using namespace std;

Radar::Radar(const string& name, const Vec2& position, double maxSpeed) : Sensor(name, position), maxSpeed(maxSpeed){}

double Radar::getMaxSpeed() const{return maxSpeed;}

void Radar::scan() const {
    cout << name << " tracking up to " << maxSpeed << " m/s..." << endl;
}