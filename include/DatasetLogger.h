#ifndef DATASETLOGGER_H 
#define DATASETLOGGER_H

#include <vector>
#include <string>
#include "Detection.h"



void writeDetections(const std::vector<Detection>& detections, const std::string& path);


#endif