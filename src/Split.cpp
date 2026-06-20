#include "Split.h"

#include <algorithm>
#include <random>


SplitData trainTestSplit(const std::vector<Sample>& samples, double trainFraction, unsigned int seed) {
    
    //create copy of the samples to shuffle
    std::vector<Sample> shuffled = samples;

    //std::mt19937 is a standard random number generator
    //std::shuffle randomly reorders the elements in the range [first, last) 
    //using the provided random number generator (rng)
    std::mt19937 rng(seed);
    std::shuffle(shuffled.begin(), shuffled.end(), rng);

    size_t trainSize = static_cast<size_t>(trainFraction * shuffled.size());


    //create the result struct and assign the training and test sets
    SplitData result;
    //assign the first trainSize samples to the training set
    //the rest to the test set
    result.trainingSet.assign(shuffled.begin(), shuffled.begin() + trainSize);
    result.testSet.assign(shuffled.begin() + trainSize, shuffled.end());

    return result;
}