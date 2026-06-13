#ifndef LIDAR_H
#define LIDAR_H
#include "Sensor.h"

class Lidar : public Sensor{

    public:
    Lidar(const std::string& name, const Vec2& position, double range);

    void scan() const override;

    double getRange() const;

    private:
    double range;
};

#endif