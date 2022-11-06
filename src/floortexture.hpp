#ifndef FLOORTEXTURE_H
#define FLOORTEXTURE_H

#include <QImage>
#include <QRgb>

#include <memory>
#include <cmath>

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
