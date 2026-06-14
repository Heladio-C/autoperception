#include "Camera.h"
#include <iostream>
using namespace std;

Camera::Camera(const string& name, const Vec2& position, double fieldOfView)
    : Sensor(name, position), fieldOfView(fieldOfView) {}

double Camera::getFieldOfView() const { return fieldOfView; }

void Camera::scan() const {
    cout << name << " capturing image at "
         << fieldOfView << "\u00b0 FOV..." << endl;
}