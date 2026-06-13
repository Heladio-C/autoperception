#ifndef VEC2_H
#define VEC2_H
#include <cmath>
#include <iomanip>

class Vec2{
    public: 
    Vec2();
    Vec2(double x, double y);

    double getX() const;
    double getY() const;

    double magnitude() const;
    double distanceTo(const Vec2& other) const;
    void print() const;




    private: 
    double x;
    double y;
};

#endif