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

static RGBColor renderTraceRay(
    const Scene &scene,
    const Ray &ray,
    const double n = 1.0,
    const short raysCount = 1
)
{
    if (raysCount >= )
    Point intersectionPoint;
    RGBColor intersectionColor;
    shared_ptr<PlaneFace> intersectedFace;
    double ks, kd, kt, kl;

    if (!scene.getIntersection(
        intersectionPoint,
        intersectionColor,
        intersectedFace,
        ks, kd, kt, kl, ray))
        return RGBColor(100, 100, 255);

    // Теневой луч
    Vector3d lightVec(
        scene.lightSource->getX() - intersectionPoint.getX(),
        scene.lightSource->getY() - intersectionPoint.getY(),
        scene.lightSource->getZ() - intersectionPoint.getZ()
    );
    Ray shadowRay(intersectionPoint, lightVec);

    // Проверяем тень, если луч прилетел вне тела
    if (eq(n, 1.0) && scene.isIntersected(shadowRay))
        return QColor(0, 0, 0);

    Vector3d normal = intersectedFace.getNormal();

    if (gt(ray.cos(normal), 0.0))
        normal.neg();

    Vector3d rayVec = ray.getVec();

    RGBColor resColor();

    // Зеркальное отражение
    if (gt(ks, 0.0))
    {
        resColor = resColor + intersectionColor * ks * pow(dot(normal, sub(lightVec, rayVec)), REF_APRROX);
        resColor = resColor + renderTraceRay(
            scene,
            sub(rayVec, mult(normal, 2 * dot(normal, ray))),
            n,
            raysCount + 1
        );
    }

    // Диффузное отражение
    if (gt(kd, 0.0))
    {
        resColor = resColor + intersectionColor * kd * lightVec.cos(normal);

        if (eq(n, 1.0))
        {
            double cosa = sqrt(1 - (1.0 / SLIME_H / SLIME_H)(1 - pow(dot(normal, ray), 2)));
            Vector3d t = sub(
                mult(ray, 1.0 / SLIME_H),
                mult(normal, cosa + 1.0 / SLIME_H * dot(normal, ray)));
            resColor = resColor + renderTraceRay(
                scene,
                t,
                SLIME_N,
                raysCount + 1
            );
        }
        else if (eq(n, SLIME_N))
        {
            double cosa = sqrt(1 - (SLIME_H * SLIME_H)(1 - pow(dot(normal, ray), 2)));
            Vector3d t = sub(
                mult(ray, SLIME_H),
                mult(normal, cosa + SLIME_H * dot(normal, ray)));
            resColor = resColor + renderTraceRay(
                scene,
                t,
                1.0,
                raysCount + 1
            );
        }
    }

    return resColor;
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

            RGBColor c = renderTraceRay(scene, fr);

            img.setPixelColor(QColor(c.getR(), c.getG(), c.getB()));
        }
    }

    pl->clear();
    pl->addPixmap(QPixmap::fromImage(img));
}
