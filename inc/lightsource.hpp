#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "object.hpp"

using namespace std;

class LightSource: public Object
{
    private:
        shared_ptr<Point> pos;
        shared_ptr<RGBColor> color;

        double i;

    public:
        Point() = default;
        Point(shared_ptr<Point> &pos) {this->pos = pos};

        ~Point() = default;

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        );
        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        );

        virtual void setPos(
            const double x,
            const double y,
            const double z
        );
        virtual void setRGB(
            const short unsigned r,
            const short unsigned g,
            const short unsigned b
        );
        virtual void setIntensity(const double i) {this->i = i;}
        
        virtual const RGBColor &getRGB() {return *color;}
        virtual const Point &getPos() {return *pos;}
        virtual double getIntensity() {return i;}
};

#endif
