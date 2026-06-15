#include "Geometry.h"
#include <algorithm> //std::max, std::min

double iou(const BoundingBox& a, const BoundingBox& b){
    //intersction is a rectangle
    const double left = std::max(a.x, b.x);
    const double top = std::max(a.y, b.y);
    const double right = std::min(a.right(), b.right());
    const double bottom = std::min(a.bottom(), b.bottom());

    //if boxes don't overlap one of the spans is <= 0
    const double overLapWidth = right - left;
    const double overLapHeight = bottom - top;

    if(overLapWidth <= 0.0 || overLapHeight <= 0.0){
        return 0.0;
    }

    const double intersectionArea = overLapHeight * overLapWidth;
    const double unionArea = a.area() + b.area() - intersectionArea;

    if(unionArea <= 0.0){
        return 0.0;
    }

    return intersectionArea/ unionArea;

}