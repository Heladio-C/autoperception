#ifndef SCALER_H
#define SCALER_H

#include <vector> 
#include "Dataset.h"


//standardize features to have mean 0 and standard deviation 1
//fit() learns mean/std from training data only
//transform() applies scaling to any dataset using learned parameters
//this prevents data leakage and ensures consistent scaling across train/test sets

class Scaler {

public: 
    void fit(const std::vector<Sample>& trainingData);
    std::vector<Sample> transform(const std::vector<Sample>& data) const;


private:
    std::vector<double> means;
    std::vector<double> stdevs;

};



#endif