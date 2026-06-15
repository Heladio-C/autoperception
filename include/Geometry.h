#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "BoundingBox.h"


//intersection over Union: how much boxes overlap from 0.0(none) to 1.0(identical)
double iou(const BoundingBox& a, const BoundingBox& b);



#endif