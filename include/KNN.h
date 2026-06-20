#ifndef KNN_H
#define KNN_H

#include <string>
#include <vector>
#include "Dataset.h"


//K nearest neighbor algorithm class
//"Training" is just storing dataset
//happens at predit time
//lazy learning algorithm

class KNN{

public: 
    //here we set the k value to 5 by default, but it can be changed when creating an instance of KNN
    //explicit because we want to prevent implicit conversions, ensuring that the constructor is only called with an integer argument for k
    explicit KNN(int k = 5) : k(k) {}

    //predict the label for a given sample based on the k nearest neighbors in the training data
    void fit(const std::vector<Sample>& train);
    std::string predict (const Sample& query) const;

    //runs prediction on the test dataset and returns accuracy 
    double evaluate(const std::vector<Sample>& test) const;


private:
    int k;
    std::vector<Sample> trainingData;
    static double distance(const Sample& a, const Sample& b);
};

#endif