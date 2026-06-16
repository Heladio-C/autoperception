#ifndef PERCEPTIONSYSTEM_H
#define PERCEPTIONSYSTEM_H

#include <vector>
#include <memory>
#include "Sensor.h"
#include "Detection.h"

class PerceptionSystem{

    public: 
    void addSensor(std::unique_ptr<Sensor> s);
    void addDetection(const Detection& d);

    //run a scan with all sensors and store results as detections
    //report all detections
    void runScan() const;
    void report() const;

    void sortByDistance(); //sort detections by distance from origin (0,0)
    const Detection& nearest() const; //find the nearest detection to the origin (0,0)

    // This is where we call the non-max suppression function to clean up our detections
    void cleanDetections(double iouThreshold = 0.5);

    private:
    
    std::vector<std::unique_ptr<Sensor>> sensors;  //base class pointers 
    std::vector<Detection> detections; //held by value
};



#endif