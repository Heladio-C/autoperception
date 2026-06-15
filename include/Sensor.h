#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include "Vec2.h"


class Sensor{

    public:
        Sensor(const std::string& name, const Vec2& position);
        virtual ~Sensor();              //virtual destructor 

        //getters
        std::string getName() const;
        Vec2 getPosition() const;
        int getId() const;

        void printInfo() const;
        
        virtual void scan() const = 0;              //virtual function makes this now abstract

        static int getCount();

    protected:
        std::string name;
        Vec2 position;
        int id;
        static int nextId;
        static int count;




};



#endif