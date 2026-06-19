#include "DataGenerator.h"
#include "BoundingBox.h"
#include "Vec2.h"
#include <random>
#include <algorithm>

//namespace for internal use only
//defines the profile for each class of objects to be generated

//pedestrians are tall and narrow
//cars are wider and shorter
//trucks are even wider and taller
namespace{
    
    struct ClassProfile{
        std::string type;
        double meanWidth, stdWidth;
        double meanHeight, stdHeight;
    };

    //1st parameter is the class type, 2nd and 3rd are mean and std for width, 4th and 5th are mean and std for height
    const std::vector<ClassProfile> profiles = {{"pedestrian", 30.0, 5.0, 80.0, 10.0}, {"car", 100.0, 12.0, 50.0, 6.0}, {"truck", 170.0, 20.0, 75.0, 9.0}};

}

std::vector<Detection> generateDataset(int samplesPerClass, unsigned int seed) {

    //std::mt19937 is a Mersenne Twister random number generator which is a widely used and efficient RNG algorithm. 
    //It is seeded with the provided seed value to ensure reproducibility of the generated dataset.
    //std::uniform_real_distribution is used to generate random confidence values between 0.5 and 1.0, simulating realistic detection confidence scores.
    std::mt19937 rng (seed); 
    std::uniform_real_distribution<double> confDist(0.5, 1.0); 

    std::vector<Detection> dataset;
    //for each class profile, generate samplesPerClass detections with dimensions based on the profile's mean and std deviation
    dataset.reserve(profiles.size() * samplesPerClass); // reserve space for efficiency

    for (const ClassProfile& profile : profiles) {

        //std::normal_distribution is used to generate random width and height values for the bounding boxes of the detections. 
        std::normal_distribution<double> widthDist(profile.meanWidth, profile.stdWidth);
        std::normal_distribution<double> heightDist(profile.meanHeight, profile.stdHeight);

        for(int i = 0; i < samplesPerClass; i++){
            //generate random width and height with gaussian variation, ensuring they are positive values
            double width = std::max(1.0, widthDist(rng));
            double height = std::max(1.0, heightDist(rng));

            Detection d {
                Vec2(0.0, 0.0), // position is not relevant for this dataset
                profile.type,
                BoundingBox{0.0, 0.0, width, height},
                confDist(rng) // random confidence between 0.5 and 1.0
            };

            dataset.push_back(d);
        }
    }
    return dataset;
}