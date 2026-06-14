#include "PerceptionSystem.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
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
    cout << "There are currently " << sensors.size() << " sensors" << endl;
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
//sort detections by distance from origin (0,0)
void PerceptionSystem::sortByDistance(){
    sort(detections.begin(), detections.end(), [](const Detection& a, const Detection& b){
        return a.position.magnitude() < b.position.magnitude();
    });
}


const Detection& PerceptionSystem::nearest() const{
    return *min_element(detections.begin(), detections.end(), [](const Detection& a, const Detection& b) {return a.position.magnitude() < b.position.magnitude();});
}