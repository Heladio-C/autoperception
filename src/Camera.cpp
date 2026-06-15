#include "Camera.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Camera::Camera(const string& name, const Vec2& position, double fieldOfView)
    : Sensor(name, position), fieldOfView(fieldOfView) {
        if(fieldOfView <= 0.0 || fieldOfView > 360.0){
            throw invalid_argument("Field of View must be in (0, 360] degrees");
        }
    }

double Camera::getFieldOfView() const { return fieldOfView; }

void Camera::scan() const {
    cout << name << " capturing image at "
         << fieldOfView << "\u00b0 FOV..." << endl;
}