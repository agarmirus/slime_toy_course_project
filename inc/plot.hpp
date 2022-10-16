#ifndef PLOT_H
#define PLOT_H

#include <memory>

#include <QGraphicsScene>

#include "scene.hpp"

using namespace std;

class Plot
{
    private:
        shared_ptr<QGraphicsScene> scene;

    public:
        Plot() = default;
        Plot(shared_ptr<QGraphicsScene> &scene) {this->scene = scene;}

        virtual ~Plot() = default;

        virtual drawScene(Scene &scene);
};

#endif
