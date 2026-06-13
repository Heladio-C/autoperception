#include "Sensor.h"
#include <iostream>
using namespace std;

int Sensor::nextId = 1000;
int Sensor::count = 0;


Sensor::Sensor(const std::string& name, const Vec2& position) : name(name), position(position), id(nextId++){
    ++count;
}

Sensor::~Sensor(){
    --count;
}

string Sensor::getName() const {
    return name;
}

Vec2 Sensor::getPosition() const {
    return position;
}

int Sensor::getId() const {
    return id;
}


void Sensor::printInfo() const {
    cout << "[#" << id << "]" << name << " @ ";
    position.print();
    cout << endl;
}

int Sensor::getCount() {
    return count;
}
