#include "KNN.h"

#include <cmath>
#include <algorithm> 
#include <map>
#include <iostream>
#include <iomanip>
#include <set>


//k-NN remembers training data and uses it to predict labels 
void KNN::fit(const std::vector<Sample>& train) {
    trainingData = train; 
}

std::string KNN::predict(const Sample& query) const{
    //we use a vector of pairs to store the distance
    //and corresponding label for each training sample
    std::vector<std::pair<double, std::string>> distances;

    //.reserve is used to allocate memory for the distances vector in advance,
    // improving performance by avoiding multiple reallocations as we push back new elements
    distances.reserve(trainingData.size());

    //calculate distance from query to each training sample
    for(const Sample& s : trainingData){
        distances.push_back({distance(query, s), s.label});
    }

    //partial sort: bring the k smallest distance to the front
    std::partial_sort(distances.begin(), distances.begin() + k, distances.end());


    //the k nearest neighbors vote on the label
    std::map<std::string, int> votes;

    for(int i = 0; i < k; ++i){
        votes[distances[i].second]++;
    }

    //return label with most votes
    std::string  best;
    int bestCount = -1; 

    //iterate through the votes map to find the label with the highest count
    for(const auto& v : votes){
        if(v.second > bestCount){
            bestCount = v.second;
            best = v.first;
        }
    }


    return best;
}

//euclidean distance between two samples
double KNN::evaluate(const std::vector<Sample>& test) const{
    if(test.empty()) return 0.0;

    int correct = 0; 
    for(const Sample& s : test) {
        if(predict(s) == s.label){
            correct++;
        }
    }

    return static_cast<double> (correct) / test.size();
}


//private helper function to calculate euclidean distance between two samples
double KNN::distance(const Sample& a, const Sample& b) {
    double sum = 0.0;
    for(size_t i = 0; i < a.features.size(); ++i){
        double diff = a.features[i] - b.features[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

KNN::ConfusionData KNN::computeConfusion(const std::vector<Sample>& test) const {
    ConfusionData cd;
 
    std::set<std::string> labelSet;
    for(const Sample& s : test){
        std::string predicted = predict(s);
        labelSet.insert(s.label);
        labelSet.insert(predicted);
        cd.counts[s.label][predicted]++;
    }
 
    cd.labels.assign(labelSet.begin(), labelSet.end());
    return cd;
}



void KNN::confusionMatrix(const std::vector<Sample>& test) const {
    // collect distinct labels (sorted for consistent order)
    //std::set is used to store unique labels from the test dataset
    std::set<std::string> labelSet;

    for(const Sample& s : test){
        labelSet.insert(s.label);
    }

    //convert set to vector for indexing
    std::vector<std::string> labels(labelSet.begin(), labelSet.end());

    //counts[true][predicted] = number of test samples
    std::map<std::string, std::map<std::string, int>> counts;

    for(const Sample& s : test){
        std::string predicted = predict(s);
        counts[s.label][predicted]++;
    }

    //header row: preidcted labels column titles

    std::cout << "Confusion Matrix (rows = actual, columns = predicated):\n\n";
    std::cout << std::left << std::setw(14) << "Actual \\ Pred";
    for(const std::string& col : labels){
        std::cout << std::setw(12) << col;
    }

    std::cout << "\n";

    //one row per true label
    for(const std::string& row : labels){
        std::cout << std::left << std::setw(14) << row;

        for(const std::string& col : labels){
            std::cout << std::setw(12) << counts[row][col];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}