#ifndef CAMERA_H
#define CAMERA_H
#include "Sensor.h"

class Camera : public Sensor{
    public:
        Camera(const std::string& name, const Vec2& position, double fieldOfVeiw);

        double getFieldOfView() const;

        void scan() const override;

    private:
        double fieldOfVeiw;

};




#endif
