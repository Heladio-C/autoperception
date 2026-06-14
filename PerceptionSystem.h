#ifndef PERCEPTIONSYSTEM_H
#define PERCEPTIONSYSTEM_H

#include <vector>
#include "Sensor.h"
#include "Detection.h"

class PerceptionSystem{

    public: 
    //destructor to clean up dynamically allocated sensors
    ~PerceptionSystem();

    //add a sensor to the system
    //add a detection to the system
    void addSensor(Sensor* s);
    void addDetection(const Detection& d);

    //run a scan with all sensors and store results as detections
    //report all detections
    void runScan() const;
    void report() const;

    void sortByDistance(); //sort detections by distance from origin (0,0)
    const Detection& nearest() const; //find the nearest detection to the origin (0,0)

    private:
    std::vector<Sensor*> sensors;  //base class pointers 
    std::vector<Detection> detections; //held by value
};



#endif