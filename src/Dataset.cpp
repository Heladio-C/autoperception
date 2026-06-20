#include "Dataset.h"

#include <fstream>
#include <sstream>



std::vector<Sample> loadDataset(const std::string& filename){
    
    std::vector<Sample> samples;
    std::ifstream file(filename);

    if(!file.is_open()){
        return samples; //return empty vector if file cannot be opened
    }

    std::string line;
    bool firstLine = true; //to skip the header line
    
    while(std::getline(file, line)){
        
        if(firstLine){
            firstLine = false;
            continue; // skip the header line
        }

        if(line.empty()){
            continue; // skip empty lines
        }  

        //split the line into features and label 
        std::istringstream ss(line);
        std::string cell;
        std::vector<std::string> cells; 

        //split the line by comma and store the cells in a vector
        while(std::getline(ss, cell, ',')){
            cells.push_back(cell);
        }

        if(cells.size() < 2){
            continue; // skip lines that don't have at least one feature and one label
        }

        Sample s;
        //all cells but last one are features, last cell is label 
        for(size_t i = 0; i < cells.size() - 1; ++i){
            //std::stod converts string to double
            s.features.push_back(std::stod(cells[i])); 
        }

        s.label = cells.back(); //last cell is the label
        samples.push_back(s);
    }

    return samples;
}
 