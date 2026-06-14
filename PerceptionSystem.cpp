#include "PerceptionSystem.h"
#include <iostream>
#include <iomanip>
using namespace std;

PerceptionSystem::~PerceptionSystem(){
    for(Sensor* s : sensors){
        delete s;
    }
}


void PerceptionSystem::addSensor(Sensor* s){
    sensors.push_back(s);
}

void PerceptionSystem::addDetection(const Detection& d){
    detections.push_back(d);
}

void PerceptionSystem::runScan() const{
    cout << "There are currently " << sensors.size() << "sensors" << endl;
    for(Sensor* s : sensors){
        s->scan();
    }
    cout << endl;
}

void PerceptionSystem::report() const{
    cout << left << setw(14) << "Type" << setw(18) << "Position"
    << "Distance" << endl;
    cout << string(40, '-') << endl;

    cout << fixed << setprecision(2);

    for(const Detection& d : detections){
        cout << left << setw(14) << d.type;
        d.position.print();
        cout << "   distance " << d.position.magnitude() << " m" << endl;
    }


}