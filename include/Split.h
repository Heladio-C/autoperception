#ifndef SPLIT_H
#define SPLIT_H


#include <vector>
#include "Dataset.h"

//holds the training and test sets after splitting the dataset
struct SplitData{
    std::vector<Sample> trainingSet;
    std::vector<Sample> testSet;
};


//shuffles the samples, via seed for reproducibility, and splits into training and test sets based on the provided ratio
//shuffling ensures that the training and test sets improvle generalization
SplitData trainTestSplit(const std::vector<Sample>& samples, double trainFraction = 0.8, unsigned int seed = 42);


#endif