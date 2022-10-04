#ifndef POINT_H
#define POINT_H

class Point
{
    private:
        double x;
        double y;
        double z;
    
    public:
        virtual void setX(const double x) {this->x = x;}
        virtual void setY(const double y) {this->y = y;}
        virtual void setZ(const double z) {this->z = z;}

        virtual double getX() {return x;}
        virtual double getY() {return y;}
        virtual double getZ() {return z;}
};

#endif
