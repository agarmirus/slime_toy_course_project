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

        virtual double getX() const {return x;}
        virtual double getY() const {return y;}
        virtual double getZ() const {return z;}

        virtual double getDistance(const Point &point) const;

        virtual bool operator==(const Point &p) const
        {
            return eq(x, p.getX()) && eq(y, p.getY()) && eq(z, p.getZ());
        }
};

Point getMiddle(const Point &p1, const Point &p2);

#endif
