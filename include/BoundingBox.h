#ifndef BOUDNING_BOX_H
#define BOUDNING_BOX_H

struct BoundingBox{

    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;

    double right() const { return x + width;}
    double bottom() const{return y + height;}
    double area() const {return width * height;}


};


#endif