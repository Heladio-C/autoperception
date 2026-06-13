#ifndef PERCEPTIONSYSTEM_H
#define PERCEPTIONSYSTEM_H

#include <vector>
#include "Sensor.h"
#include "Detection.h"

class PerceptionSystem{

    public: 
    ~PerceptionSystem();

    void addSensor(Sensor* s);
    void addDetection(const Detection& d);

    void runScan() const;
    void report() const;


    private:
    std::vector<Sensor*> sensors;  //base class pointers 
    std::vector<Detection> detections; //held by value



};



#endif