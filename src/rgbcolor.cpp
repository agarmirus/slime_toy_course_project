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

    if (r < 0)
        r = 0;
    if (g < 0)
        g = 0;
    if (b < 0)
        b = 0;
}

RGBColor RGBColor::operator+(const RGBColor &color) const
{
    RGBColor res = *this;
    res.sum(color);

    return res;
}

RGBColor RGBColor::operator*(const double k) const
{
    RGBColor res = *this;
    res.mult(k);

    return res;
}

RGBColor operator*(const double k, const RGBColor &color)
{
    RGBColor res = color;

    res = res * k;

    return res;
}

RGBColor sum(const RGBColor &c1, const RGBColor &c2)
{
    return c1 + c2;
}

RGBColor mult(const RGBColor &c, const double k)
{
    return c * k;
}
