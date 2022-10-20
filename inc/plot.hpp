#ifndef PLOT_H
#define PLOT_H

#include <memory>

#include <QGraphicsScene>

#include "scene.hpp"

using namespace std;

class Plot
{
    private:
        shared_ptr<QGraphicsScene> pl;

    public:
        Plot() = default;
        Plot(shared_ptr<QGraphicsScene> &pl) {this->pl = pl;}

        virtual ~Plot() = default;

        virtual drawScene(Scene &scene);
};

#endif
