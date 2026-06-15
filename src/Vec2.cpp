#include "Vec2.h"
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;


//constructors
Vec2::Vec2() : x(0.0), y(0.0) {}

Vec2::Vec2(double x, double y) : x(x), y(y) {}


//getters
double Vec2::getX() const {
    return x;
}

double Vec2::getY() const {
    return y;
}


//other member functions
double Vec2::magnitude() const {
    return sqrt(x * x + y * y);
}

double Vec2::distanceTo(const Vec2& rhs) const {
    double dx = x - rhs.x;
    double dy = y - rhs.y;

    return sqrt(dx * dx + dy * dy);
}

void Vec2::print() const {

    cout << fixed << setprecision(2) << "(" << x << ", " << y << ")";
}


//operator overloading
Vec2 Vec2::operator+(const Vec2& rhs) const{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

bool Vec2::operator==(const Vec2& rhs) const{
    return ((x == rhs.x) && (y == rhs.y));
}

std::ostream& operator<<(std::ostream& os, const Vec2& rhs) {
    os << fixed << setprecision(2)
    << "(" << rhs.x << ", " << rhs.y << ")";
    return os;
}
