#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <cmath>

class RGBColor
{
    private:
        short r;
        short g;
        short b;
    
    public:
        RGBColor() = default;
        RGBColor(const short r, const short g, const short b);

        virtual void sum(const RGBColor &color);
        virtual void mult(const double k);

        virtual void setR(const short r) {this->r = r;}
        virtual void setG(const short g) {this->g = g;}
        virtual void setB(const short b) {this->b = b;}

        virtual short int getR() {return r;}
        virtual short int getG() {return g;}
        virtual short int getB() {return b;}
};

#endif
