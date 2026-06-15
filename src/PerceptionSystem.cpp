#include "PerceptionSystem.h"
#include "PerceptionError.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>      // std::move
using namespace std;

// destructor removed — unique_ptr cleans up each sensor automatically

void PerceptionSystem::addSensor(unique_ptr<Sensor> s) {
    sensors.push_back(move(s));     // transfer ownership into the vector
}

void PerceptionSystem::addDetection(const Detection& d) {
    detections.push_back(d);
}

void PerceptionSystem::runScan() const {
    cout << "-- running " << sensors.size() << " sensors --" << endl;
    for (const auto& s : sensors) {
        s->scan();                  // -> works just like with a raw pointer
    }
    cout << endl;
}

void PerceptionSystem::report() const {
    cout << left << setw(14) << "Type" << "Position / Distance" << endl;
    cout << string(40, '-') << endl;

    cout << fixed << setprecision(2);
    for (const Detection& d : detections) {
        cout << left << setw(14) << d.type
             << d.position
             << "   distance " << d.position.magnitude() << " m" << endl;
    }
}

void PerceptionSystem::sortByDistance() {
    sort(detections.begin(), detections.end(),
        [](const Detection& a, const Detection& b) {
            return a.position.magnitude() < b.position.magnitude();
        });
}

const Detection& PerceptionSystem::nearest() const {
    if (detections.empty()) {
        throw PerceptionError("nearest() called but no detections exist");
    }
    return *min_element(detections.begin(), detections.end(),
        [](const Detection& a, const Detection& b) {
            return a.position.magnitude() < b.position.magnitude();
        });
}