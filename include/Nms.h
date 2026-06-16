#ifndef NMS_H
#define NMS_H

#include <vector>
#include "Detection.h"


//Non max superession: remove cluster of overlapping detections down to one per object. 
//keep highest confidence score, and discard boxes that overlapes already kept box, by more than iou threshold. 
std::vector<Detection> nonMaxSupression(std::vector<Detection> detections, double iouThreshold = 0.5);


#endif