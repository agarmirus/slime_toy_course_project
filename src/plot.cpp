#include "plot.hpp"

Plot::Plot(
    shared_ptr<QGraphicsScene> &pl,
    const size_t width,
    const size_t height
)
{
    this->pl = pl;
    w = width / 2;
    h = height / 2;

    img = QImage(width, height);
}

static QColor renderTraceRay(
    const Scene &scene,
    const Ray &ray,
    const double n = 1.0,
    const short raysCount = 1
)
{
    Point intersectionPoint;
    RGBColor intersectionColor;
    shared_ptr<PlaneFace> intersectedFace;
    double ks, kd, kt, kl;

    if (!scene.getIntersection(
        intersectionPoint,
        intersectionColor,
        intersectedFace,
        ks, kd, kt, kl,ray))
        return QColor(100, 100, 255);

    // Теневой луч
    Ray shadowRay(
        intersectionPoint,
        Vector3d(
            scene.lightSource->getX() - intersectionPoint.getX(),
            scene.lightSource->getY() - intersectionPoint.getY(),
            scene.lightSource->getZ() - intersectionPoint.getZ()
        )
    );
}

// распараллелить
void Plot::drawScene(const Scene &scene)
{
    Point camPos = scene.getCamera()->getPos();

    double cx = camPos.getX();
    double cy = camPos.getY();
    double cz = camPos.getZ();

    double d = h / tan(FOV / 2);

    for (size_t i = 0; i < h << 2; ++i)
    {
        for (size_t j = 0; j < w << 2; ++j)
        {
            Vector3d dij(j - w, i - h, d);
            Point frPos(cx, cy, cz);

            Ray fr(dij, frPos);

            img.setPixelColor(renderTraceRay(scene, fr));
        }
    }

    pl->clear();
    pl->addPixmap(QPixmap::fromImage(img));
}
