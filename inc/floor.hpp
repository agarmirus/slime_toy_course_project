#ifndef FLOOR_H
#define FLOOR_H

#include "object.hpp"
#include "texture.hpp"

#include <memory>

#include "doubleop.hpp"

using namespace std;

class Floor: public Object
{
    private:
        shared_ptr<Texture> texture;

        double kd;
    
    public:
        Floor() = default;
        Floor(
            const double kd, const double ks, const double kt,
            const shared_ptr<Texture> &texture
        );

        virtual ~Floor() = default;

        virtual void setKd(const double kd) {this->kd = kd;}

        virtual bool getIntersection(
            Point &pos,
            RGBColor &color,
            shared_ptr<PlaneFace> &face,
            double &ks,
            double &kd,
            double &kt,
            double &kl,
            const Ray &ray
        );

        virtual double getKd() {return kd;}
};

#endif
