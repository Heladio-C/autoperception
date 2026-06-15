#include "Radar.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Radar::Radar(const string& name, const Vec2& position, double maxSpeed) : Sensor(name, position), maxSpeed(maxSpeed){

    if(maxSpeed <= 0.0){
        throw invalid_argument("Radar max speed must be positive");
    }
}

double Radar::getMaxSpeed() const{return maxSpeed;}

void Radar::scan() const {
    cout << name << " tracking up to " << maxSpeed << " m/s..." << endl;
}