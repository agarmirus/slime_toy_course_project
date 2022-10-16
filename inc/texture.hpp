#ifndef TEXTURE_H
#define TEXTURE_H

#include "rgbcolor.hpp"

class Texture
{
    public:
        virtual RGBColor getColor() = 0;
};

#endif
