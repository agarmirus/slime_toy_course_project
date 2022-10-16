#ifndef FLOORTEXTURE_H
#define FLOORTEXTURE_H

#include <memory>
#include <tiffio.h>
#include <string>

#include "texture.hpp"

class FloorTexture: public Texture
{
    private:
        shared_ptr<TIFF> pic;
    
    public:
        FloorTexture(string &filename);

        virtual ~FloorTexture();

        virtual RGBColor getColor();
}

#endif
