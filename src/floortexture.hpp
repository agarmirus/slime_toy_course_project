#ifndef FLOORTEXTURE_H
#define FLOORTEXTURE_H

#include <QImage>
#include <QRgb>

#include <memory>
#include <string>
#include <cmath>

#include "texture.hpp"

class FloorTexture: public Texture
{
    private:
        int width;
        int height;

        QRgb *line;
    public:
        FloorTexture(const string &filename);

        virtual ~FloorTexture() = default;

        virtual RGBColor getColor(const Point &pos);
}

#endif
