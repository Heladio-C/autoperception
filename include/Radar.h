#ifndef RADAR_H
#define RADAR_H
#include "Sensor.h"

class Radar : public Sensor{
    public:
        Radar(const std::string& name, const Vec2& position, double maxSpeed);

        double getMaxSpeed() const;

        void scan() const override;

    private:
        double maxSpeed;
};

#endif