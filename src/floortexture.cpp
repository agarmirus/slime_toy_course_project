#include "floortexture.hpp"

FloorTexture::FloorTexture(const char *filename)
{
    img = make_shared<QImage>(filename);

    width = img->width();
    height = img->height();
}

RGBColor FloorTexture::getColor(const Point &pos) const
{
    int w = int(fabs(pos.getX())) % width;
    int h = int(fabs(pos.getY())) % height;

    QColor color = img->pixel(w, h);

    RGBColor res(color.red(), color.green(), color.blue());

    return res;
}
