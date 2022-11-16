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

        double ka;
        double ks;
        double kd;
        double kt;
        double kl;
    
    public:
        Floor() = default;
        Floor(
            const double ka,
            const double kd,
            const double ks,
            const double kt,
            const shared_ptr<Texture> &texture
        );

        virtual ~Floor() = default;

        virtual void update(const size_t ms) {return;}

        virtual void setKa(const double ka) {this->ka = ka;}
        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}
        virtual void setKl(const double kl) {this->kl = kl;}

        virtual bool getIntersection(
            Point &pos,
            RGBColor &color,
            shared_ptr<PlaneFace> &face,
            double &ka,
            double &ks,
            double &kd,
            double &kt,
            double &kl,
            const Ray &ray
        ) const;

        virtual double getKa() const {return ka;}
        virtual double getKd() const {return kd;}
        virtual double getKs() const {return ks;}
        virtual double getKt() const {return kt;}
        virtual double getKl() const {return kl;}

        virtual bool isIntersected(const Ray &ray) const;
};

#endif
