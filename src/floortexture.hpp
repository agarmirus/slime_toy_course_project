#ifndef FLOORTEXTURE_H
#define FLOORTEXTURE_H

#include <cmath>
#include <memory>

#include <QRgb>
#include <QImage>

#include "texture.hpp"

using namespace std;

class FloorTexture: public Texture
{
    private:
        int width;
        int height;

        shared_ptr<QImage> img;
    public:
        explicit FloorTexture(const char *filename);

        virtual ~FloorTexture() = default;

        virtual RGBColor getColor(const Point &pos) const;
};

#endif
