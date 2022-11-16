#ifndef PLOT_H
#define PLOT_H

#include <memory>
#include <stack>
#include <cmath>

#include <QGraphicsScene>

#include "scene.hpp"
#include "omp.h"

#define FOV M_PI / 3

#define MAX_TRACE_COUNT 5
#define REF_APRROX 2
#define SLIME_N 1.005
#define MAX_RAYS_COUNT 5

// #define VIEW_W 1144
// #define VIEW_H 817

#define VIEW_W 600
#define VIEW_H 370

using namespace std;

class Plot
{
    private:
        QGraphicsScene* pl;

        shared_ptr<QImage> img;

        int w;
        int h;

    public:
        Plot() = default;
        Plot(
            QGraphicsScene *pl,
            const int width,
            const int height
        );

        virtual ~Plot() = default;

        virtual void drawScene(const shared_ptr<Scene> &scene);
};

#endif
