#ifndef DETECTION_H
#define DETECTION_H

#include <string> 
#include "Vec2.h"
#include "BoundingBox.h"

struct Detection{

    Vec2 position;
    std::string type;

    BoundingBox box;
    double confidence = 0.0;

};

#endif