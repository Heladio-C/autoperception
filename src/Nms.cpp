#include "Nms.h"
#include "Geometry.h"

#include <algorithm>

std::vector<Detection> nonMaxSupression(std::vector<Detection> detections, double iouThreshold){


    std::sort(detections.begin(), detections.end(), [](const Detection& a, const Detection& b){
        return a.confidence > b.confidence;
    });

    std::vector<Detection> kept;

    for(const Detection& candidate : detections){
        bool overLapsAKeptBox = false;
        for(const Detection& winner : kept){
            if(iou(candidate.box , winner.box) > iouThreshold){
                overLapsAKeptBox = true;
                break;
            }
        }
        if(!overLapsAKeptBox){
            kept.push_back(candidate);
        }
    }

    return kept;
}