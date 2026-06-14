#ifndef VEC2_H
#define VEC2_H
#include <cmath>
#include <iomanip>

class Vec2{
    public: 
    //constructors
    Vec2();
    Vec2(double x, double y);

    //operator overloading
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    bool operator==(const Vec2& rhs) const;

    //friend function for output stream operator
    friend std::ostream& operator <<(std::ostream& os, const Vec2& v);


    //getters
    double getX() const;
    double getY() const;
    

    //other member functions
    double magnitude() const;
    double distanceTo(const Vec2& other) const;
    void print() const;




    private: 
    double x;
    double y;
};

#endif