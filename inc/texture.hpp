#ifndef TEXTURE_H
#define TEXTURE_H

#include "rgbcolor.hpp"
#include "point.hpp"

class Texture
{
    public:
        virtual RGBColor getColor(const Point &pos) = 0;
};

#endif
