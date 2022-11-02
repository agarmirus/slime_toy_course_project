#include "floortexture.hpp"

FloorTexture::FloorTexture(const char *filename)
{
    img = make_shared<QImage>(filename);

    width = img->width();
    height = img->height();

    QRgb *line = (QRgb *)img->constBits();
}

RGBColor FloorTexture::getColor(const Point &pos) const
{
    int w = int(pos.getX() + 0.5) % width;
    int h = int(pos.getY() + 0.5) % height;

    QColor color(*(line + h * width + w));

    RGBColor res(color.red(), color.green(), color.blue());

    return res;
}
