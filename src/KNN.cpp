#include "KNN.h"

#include <cmath>
#include <algorithm> 
#include <map>


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