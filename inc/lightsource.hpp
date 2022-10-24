#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "object.hpp"

using namespace std;

class LightSource: public Object
{
    private:
        shared_ptr<Point> pos;
        RGBColor color;

        double i;

    public:
        Point() = default;
        Point(const shared_ptr<Point> &pos) {this->pos = pos};

        ~Point() = default;

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        ) {pos->move(dx, dy, dz);}

        virtual void setPos(const shared_ptr<Point> &pos) {this->pos = pos;}
        virtual void setRGB(const RGBColor &color) {this->color = color;}
        virtual void setIntensity(const double i) {this->i = i;}
        
        virtual RGBColor getRGB() {return color;}
        virtual const Point getPos() {return *pos;}
        virtual double getIntensity() {return i;}
};

#endif
