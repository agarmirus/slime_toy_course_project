#ifndef PLOT_H
#define PLOT_H

#include <pthread.h>
#include <time.h>
#include <memory>
#include <cmath>

#include <QPixmap>
#include <QGraphicsScene>

#include "scene.hpp"

#define FOV M_PI / 3

#define MAX_TRACE_COUNT 5
#define REF_APRROX 5
#define SLIME_N 1.1
#define MAX_RAYS_COUNT 5

// #define VIEW_W 1144
// #define VIEW_H 817

#define VIEW_W 600
#define VIEW_H 370

using namespace std;

struct RanderData
{
    int w;
    int h;
    int hn;
    shared_ptr<Scene> scene;
    QImage *buf;
};

using RanderData = struct RanderData;

class Plot
{
    private:
        shared_ptr<QImage> img;

        int w;
        int h;

    public:
        Plot() = default;
        Plot(
            const int width,
            const int height
        );

        virtual ~Plot() = default;

        virtual void drawScene(const shared_ptr<Scene> &scene);

        virtual void updateGraphicsScene(void *const scene);
};

#endif
