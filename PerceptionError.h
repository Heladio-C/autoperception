#ifndef PERCEPTIONERROR_H
#define PERCEPTIONERROR_H

#include <stdexcept>
#include <string>

class PerceptionError : public std::runtime_error {
    public:
    explicit PerceptionError(const std::string& message) : std::runtime_error(message){}

};



#endif