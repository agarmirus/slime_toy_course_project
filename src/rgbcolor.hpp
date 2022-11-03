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

        virtual short int getR() const {return r;}
        virtual short int getG() const {return g;}
        virtual short int getB() const {return b;}

        virtual RGBColor operator+(const RGBColor &color) const;
        virtual RGBColor operator*(const double k) const;
};

RGBColor operator*(const double k, const RGBColor &color);

RGBColor sum(const RGBColor &c1, const RGBColor &c2);

RGBColor mult(const RGBColor &c, const double k);

#endif
