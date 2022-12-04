#include "plot.hpp"

// #include <chrono>
// #include <stdio.h>

Plot::Plot(
    const int width,
    const int height
)
{
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
    double ka, ks, kd, kt, kl;

    if (!scene->getIntersection(
        intersectionPoint,
        intersectionColor,
        intersectedFace,
        ka, ks, kd, kt, kl, ray))
        return RGBColor(100, 100, 255);
    
    if (gt(ka, 0.0))
        resColor = intersectionColor * ka;

    Point lightPos = scene->getLightSource()->getPos();

    Vector3d lightVec(intersectionPoint, lightPos);

    Vector3d rayVec = normalize(ray.getVec());
    Vector3d normal = normalize(intersectedFace->getNormal());

    if (gt(rayVec.cos(normal), 0.0))
        normal.neg();
    
    // Диффузное отражение
    if (gt(kd, 0.0))
    {
        Ray shadowRay(lightVec, intersectionPoint);

        // Проверяем тень, если луч прилетел извне
        if (!scene->isIntersected(shadowRay))
            resColor = resColor + intersectionColor * kd * fabs(lightVec.cos(normal));
    }

    // Зеркальное отражение
    if (gt(ks, 0.0))
    {
        resColor = resColor + intersectionColor * ks * pow(neg(rayVec).cos(lightVec), REF_APRROX);
        resColor = resColor + ks * renderTraceRay(
            scene,
            Ray(rayVec - normal * (2 * (normal * rayVec)), intersectionPoint),
            n,
            raysCount + 1
        );
    }

    // Преломление
    if (gt(kt, 0.0))
    {
        double n1 = 1.0;
        double n2 = SLIME_N;

        if (ne(n, 1.0))
        {
            double tmp = n1;
            n1 = n2;
            n2 = tmp;
        }

        double d = rayVec * normal;
        Vector3d rv = rayVec - ((d * normal) + \
        (sqrt(n2 * n2 - n1 * n1 + d * d) * normal));

        double ie = gt(kl, 0.0) ? exp(-kl * ray.getPos().getDistance(intersectionPoint)) : 1.0;

        resColor = resColor + kt * ie * renderTraceRay(
            scene,
            Ray(rv, intersectionPoint),
            n2,
            raysCount + 1
        );
    }

    return resColor;
}

static void *render(void *data)
{
    auto rdata = static_cast<RanderData *>(data);
    shared_ptr<Scene> scene = rdata->scene;
    int w = rdata->w;
    int h = rdata->h;
    int hn = rdata->hn;
    QImage *buf = rdata->buf;

    Point camPos = scene->getCamera()->getPos();

    double cx = camPos.getX();
    double cy = camPos.getY();
    double cz = camPos.getZ();

    double d = h / tan(FOV / 2);

    for (int i = 0; i < 2 * w; ++i)
    {
        Vector3d dij(i - w, d, h - hn);
        Point frPos(cx, cy, cz);

        Ray fr(dij, frPos);

        RGBColor c = renderTraceRay(scene, fr);

        buf->setPixelColor(i, hn, QColor(c.getR(), c.getG(), c.getB()));
    }

    return nullptr;
}

void Plot::drawScene(const shared_ptr<Scene> &scene)
{
    QImage buf(w * 2, h * 2, QImage::Format_RGB32);

    RanderData *data = new RanderData[VIEW_H];
    pthread_t *threads = new pthread_t[VIEW_H];

    // auto start = chrono::steady_clock::now();
    for (int i = 0; i < VIEW_H; ++i)
    {
        data[i].w = w;
        data[i].h = h;
        data[i].hn = i;
        data[i].scene = scene;
        data[i].buf = &buf;

        pthread_create(threads + i, NULL, render, data + i);
    }
    // auto end = chrono::steady_clock::now();

    // printf("%ld\n", chrono::duration_cast<chrono::milliseconds>(end - start).count());

    for (int i = 0; i < VIEW_H; ++i)
        pthread_join(threads[i], nullptr);
    
    delete[] data;
    delete[] threads;
    
    *img = buf;
}

void Plot::updateGraphicsScene(void *const scene)
{
    auto qtscene = (QGraphicsScene *)scene;
    qtscene->clear();
    qtscene->addPixmap(QPixmap::fromImage(*img));
}
