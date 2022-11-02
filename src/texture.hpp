#ifndef TEXTURE_H
#define TEXTURE_H

#include "rgbcolor.hpp"
#include "point.hpp"

class Texture
{
    public:
        virtual RGBColor getColor(const Point &pos) const = 0;
};

#endif
