#include "DatasetLogger.h"
#include <fstream>

void writeDetections(const std::vector<Detection>& detections, const std::string& path){

    // check if file is empty
    // if file is empty write header
    std::ifstream file(path);
    bool isEmpty = file.peek() == std::ifstream::traits_type::eof();
    file.close();


    // open file for appending
    std::ofstream out(path, std::ios::app);
    if(!out.is_open()){
        return;
    }


    // write detections
    if(isEmpty){
        out << "width, height, aspect_ratio, area, confidence, type\n";
    }

    for(const Detection& d : detections){
        double width = d.box.width;
        double height = d.box.height;

        double aspectRatio = (height != 0.0) ? width / height : 0.0;

        out << width << "," << height << "," << aspectRatio << "," << d.box.area() << "," << d.confidence << "," << d.type << "\n";
    }
    out.close();
}