#include "plot.hpp"

Plot::Plot(
    QGraphicsScene *pl,
    const int width,
    const int height
)
{
    this->pl = pl;
    w = width / 2;
    h = height / 2;

    img = make_shared<QImage>(width, height, QImage::Format_RGB32);
}

static RGBColor renderTraceRay(
    const shared_ptr<Scene> &scene,
    const Ray &ray,
    const double n = 1.0,
    const short raysCount = 1
)
{
    RGBColor resColor(0, 0, 0);

    if (raysCount >= MAX_RAYS_COUNT)
        return resColor;
    
    Point intersectionPoint;
    RGBColor intersectionColor;
    shared_ptr<PlaneFace> intersectedFace;
    double ks, kd, kt, kl;

    if (!scene->getIntersection(
        intersectionPoint,
        intersectionColor,
        intersectedFace,
        ks, kd, kt, kl, ray))
        return RGBColor(100, 100, 255);

    Point lightPos = scene->getLightSource().getPos();

    // Теневой луч
    Vector3d lightVec(intersectionPoint, lightPos);
    Ray shadowRay(lightVec, intersectionPoint);

    // Проверяем тень, если луч прилетел извне
    if (eq(n, 1.0) && scene->isIntersected(shadowRay))
        return resColor;

    Vector3d rayVec = ray.getVec();
    Vector3d normal = intersectedFace->getNormal();

    if (gt(rayVec.cos(normal), 0.0))
        normal.neg();

    // Зеркальное отражение
    if (gt(ks, 0.0))
    {
        resColor = resColor + intersectionColor * ks * pow(dot(normal, sub(lightVec, rayVec)), REF_APRROX);
        resColor = resColor + ks * renderTraceRay(
            scene,
            Ray(sub(rayVec, mult(normal, 2 * dot(normal, rayVec) / dot(normal, normal))), intersectionPoint),
            n,
            raysCount + 1
        );
    }

    // Преломление
    if (gt(kt, 0.0))
    {
        // if (eq(n, 1.0))
        // {
        //     double cosa = sqrt(1.0 - 1.0 / (SLIME_N * SLIME_N) * (1.0 - pow(dot(normal, rayVec), 2)));
        //     Vector3d t = sub(
        //         mult(rayVec, 1.0 / SLIME_N),
        //         mult(normal, cosa + 1.0 / SLIME_N * dot(normal, rayVec))
        //     );
        //     resColor = resColor + kt * renderTraceRay(
        //         scene,
        //         Ray(t, intersectionPoint),
        //         SLIME_N,
        //         raysCount + 1
        //     );
        // }
        // else if (eq(n, SLIME_N))
        // {
        //     double cosa = sqrt(1.0 - (SLIME_N * SLIME_N) * (1.0 - pow(dot(normal, rayVec), 2)));
        //     Vector3d t = sub(
        //         mult(rayVec, SLIME_N),
        //         mult(normal, cosa + SLIME_N * dot(normal, rayVec))
        //     );
        //     if (gt(kl, 0.0))
        //         resColor = resColor + exp(-kl * ray.getPos().getDistance(intersectionPoint)) * kt * renderTraceRay(
        //             scene,
        //             Ray(t, intersectionPoint),
        //             1.0,
        //             raysCount + 1
        //         );
        //     else
        //         resColor = resColor + kt * renderTraceRay(
        //             scene,
        //             Ray(t, intersectionPoint),
        //             1.0,
        //             raysCount + 1
        //         );
        // }

        double n1 = 1.0;
        double n2 = SLIME_N;

        if (eq(n, 1.0))
        {
            double tmp = n1;
            n1 = n2;
            n2 = tmp;
        }

        Vector3d rv = 
    }

    // Диффузное отражение
    if (eq(n, 1.0) && gt(kd, 0.0))
        resColor = resColor + intersectionColor * kd * lightVec.cos(normal);

    return resColor;
}

void Plot::drawScene(const shared_ptr<Scene> &scene)
{
    Point camPos = scene->getCamera().getPos();

    double cx = camPos.getX();
    double cy = camPos.getY();
    double cz = camPos.getZ();

    double d = h / tan(FOV / 2);

    for (int i = 0; i < (h << 1); ++i)
    {
        for (int j = 0; j < (w << 1); ++j)
        {
            Vector3d dij(j - w, d, h - i);
            Point frPos(cx, cy, cz);

            Ray fr(dij, frPos);

            RGBColor c = renderTraceRay(scene, fr);

            img->setPixelColor(j, i, QColor(c.getR(), c.getG(), c.getB()));
        }
    }

    pl->clear();
    pl->addPixmap(QPixmap::fromImage(*img));
}
