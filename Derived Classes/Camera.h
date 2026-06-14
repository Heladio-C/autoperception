#ifndef CAMERA_H
#define CAMERA_H

#include "Sensor.h"

class Camera : public Sensor {
private:
    double fieldOfView;  //degrees

public:
    Camera(const std::string& name, const Vec2& position, double fieldOfView);

    double getFieldOfView() const;

    void scan() const override;
};

#endif