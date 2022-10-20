#ifndef POINT_H
#define POINT_H

#include <cmath>

#include "doubleop.hpp"

class Point
{
    private:
        double x;
        double y;
        double z;
    
    protected:
        void turnAroundOZ(const double angle);
        void turnAroundOY(const double angle);
        void turnAroundOX(const double angle);

        void moveToCenter(const Point &center);
        void returnFromCenter(const Point &center);

        double toRad(const double deg) {return deg * PI / 180;}
    
    public:
        Point() = default;
        Point(
            const double x,
            const double y,
            const double z
        );

        virtual ~Point() = default;

        virtual void setX(const double x) {this->x = x;}
        virtual void setY(const double y) {this->y = y;}
        virtual void setZ(const double z) {this->z = z;}

        virtual double getX() {return x;}
        virtual double getY() {return y;}
        virtual double getZ() {return z;}

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        );
        virtual void rotate(
            const Point &center,
            const double xAngle,
            const double yAngle,
            const double zAngle
        );

        virtual bool operator==(const Point &p)
        {
            return eq(x, p.getX()) && eq(y, p.getY()) && eq(z, p.getZ());
        }
};

#endif
