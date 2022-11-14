#include "floortexture.hpp"

FloorTexture::FloorTexture(const char *filename)
{
    img = make_shared<QImage>(filename);

    width = img->width();
    height = img->height();
}

RGBColor FloorTexture::getColor(const Point &pos) const
{
    int x = int(pos.getX()) % width;
    int y = int(pos.getY()) % height;


    int w = x < 0 ? width + x : x;
    int h = y < 0 ? height + y : y;

    QColor color = img->pixel(w, h);

    RGBColor res(color.red(), color.green(), color.blue());

    return res;
}
