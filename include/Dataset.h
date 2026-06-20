#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>


//a vector of numerica features and a string label
struct Sample{

    std::vector<double> features;
    std::string label;
};


//loads a dataset from the csv file and returns a vector of samples
std::vector<Sample> loadDataset(const std::string& filename);

#endif