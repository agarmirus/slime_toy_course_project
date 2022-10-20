#include "floortexture.hpp"

FloorTexture::FloorTexture(string &filename)
{
    QImage img(filename);

    width = img.width;
    height = img.height;

    QRgb *line = (QRgb *)img.constBits();
}

RGBColor FloorTexture::getColor(const Point &pos)
{
    int w = round(pos.getX() + 0.5) % width;
    int h = round(pos.getY() + 0.5) % height;

    QColor color(*(line + h * width + w));

    RGBColor res(color.red(), color.green(), color.blue());

    return res;
}
