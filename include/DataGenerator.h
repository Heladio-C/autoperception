#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include "Detection.h"

//generates a dataset of detections with random values for width, height, confidence and type
//types are randomly assigned from a predefined set of classes (e.g., "car", "pedestrian", "bicycle")
//dimensions with gaussian variation produces samplesPerClass
//rows per class. seed makes the dataset reproducible

std::vector<Detection> generateDataset(int samplesPerClass, unsigned int seed = 42);


#endif