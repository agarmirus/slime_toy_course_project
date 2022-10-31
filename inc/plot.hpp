#ifndef PLOT_H
#define PLOT_H

#include <memory>
#include <stack>
#include <cmath>

#include <QGraphicsScene>

#include "scene.hpp"

#define FOV PI / 3

#define MAX_TRACE_COUNT 5

#define REF_APRROX 2

#define SLIME_N 1.5

#define MAX_RAYS_COUNT 5

using namespace std;

class Plot
{
    private:
        QGraphicsScene* pl;

        QImage img;

        size_t w;
        size_t h;

    public:
        Plot() = default;
        Plot(
            shared_ptr<QGraphicsScene> &pl,
            const size_t width,
            const size_t height
        );

        virtual ~Plot() = default;

        virtual void drawScene(const Scene &scene);
};

#endif
