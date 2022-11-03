#ifndef FLOOR_H
#define FLOOR_H

#include "object.hpp"
#include "texture.hpp"
#include "planeface.hpp"

#include <memory>

#include "doubleop.hpp"

using namespace std;

class Floor: public Object
{
    private:
        shared_ptr<Texture> texture;
        shared_ptr<PlaneFace> face;

        double ks;
        double kd;
        double kt;
        double kl;
    
    public:
        Floor() = default;
        Floor(
            const double kd, const double ks, const double kt,
            const shared_ptr<Texture> &texture
        );

        virtual ~Floor() = default;

        virtual void update(const size_t ms) {return;}

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
        ) const;

        virtual double getKd() const {return kd;}

        virtual bool isIntersected(const Ray &ray) const;
};

#endif
