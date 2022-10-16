#include "rgbcolor.hpp"

RGBColor::RGBColor(const short r, const short g, const short b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void RGBColor::sum(const RGBColor &color)
{
    r += color.getR();
    g += color.getG();
    b += color.getB();

    if (r > 255)
        r = 255;
    
    if (g > 255)
        g = 255;
    
    if (b > 255)
        b = 255;
}

void RGBColor::mult(const double k)
{
    r = round(r * k);
    g = round(g * k);
    b = round(b * k);

    if (r > 255)
        r = 255;
    
    if (g > 255)
        g = 255;
    
    if (b > 255)
        b = 255;
}
