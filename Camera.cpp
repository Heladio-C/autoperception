#include "Camera.h"
#include <iostream>

using namespace std;

Camera::Camera(const string& name, const Vec2& position, double fieldOfVeiw) : Sensor(name, position), fieldOfVeiw(fieldOfVeiw) {}

double Camera::getFieldOfView() const {return fieldOfVeiw;}

void Camera::scan() const {
    cout << name << " capturing image at " << fieldOfVeiw << "\u00b0 FOV..." << endl;
}