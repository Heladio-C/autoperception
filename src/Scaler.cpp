#include "Scaler.h"
#include <cmath>

void Scaler::fit(const std::vector<Sample>& trainingData) {
    if(trainingData.empty()) return;
    
    size_t numFeatures = trainingData[0].features.size();
    //initialize means and stdevs
    means.assign(numFeatures, 0.0);
    stdevs.assign(numFeatures, 0.0);


    //mean of each feature across training set
    for(const Sample& s : trainingData){
        for(size_t i = 0; i < numFeatures; ++i){
            means[i] += s.features[i];
        }
    }

    for(size_t i = 0; i < numFeatures; ++i){
        means[i] /= trainingData.size();
    }

    //standard deviation of each feature across training set
    for(const Sample& s : trainingData) {
        for(size_t i = 0; i < numFeatures; ++i){
            double diff = s.features[i] - means[i];
            stdevs[i] += diff * diff;
        }
    }

    for(size_t i = 0; i < numFeatures; ++i){
        stdevs[i] = std::sqrt(stdevs[i] / trainingData.size());
        //prevent division by zero
        if(stdevs[i] == 0.0) stdevs[i] = 1.0;
    }
}


std::vector<Sample> Scaler::transform(const std::vector<Sample>& data) const{
    //copy data to output vector
    std::vector<Sample> out = data;
    
    //apply scaling to each feature of each sample
    for(Sample& s : out){
        for(size_t i = 0; i < s.features.size(); ++i){
            s.features[i] = (s.features[i] - means[i]) / stdevs[i];
        }
    }

    return out;
}