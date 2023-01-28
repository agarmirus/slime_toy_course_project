#ifndef SLIME_H
#define SLIME_H

#include <pthread.h>

#include "object.hpp"
#include "doubleop.hpp"
#include "masspoint.hpp"
#include "spherecover.hpp"

#define G 9.81e-3

#define THREAD_POINTS_COUNT 8

using namespace std;

#define MP_LIST_ITERATOR_TYPE std::__cxx11::list<std::shared_ptr<MassPoint>>::iterator

struct PhysData
{
    MP_LIST_ITERATOR_TYPE b;
    MP_LIST_ITERATOR_TYPE e;

    double k;
    double kdmp;
};

class Grabber;

class Slime: public Object
{
    friend Grabber;
    
    private:
        list<shared_ptr<MassPoint>> massPoints;
        list<shared_ptr<PlaneFace>> faces;

        SphereCover cover;

        double mass;
        double k;
        double kdmp;
        
        double ka;
        double kd;
        double ks;
        double kt;
        double kl;

        RGBColor color;
    
    public:
        Slime() = default;

        virtual ~Slime() = default;
        
        virtual void update(const size_t ms);
        virtual void updateCover();

        virtual void setMass(const double mass);
        virtual void setStiffness(const double k) {this->k = k;}
        virtual void setDamp(const double kdmp) {this->kdmp = kdmp;}
        virtual void setKa(const double ka) {this->ka = ka;}
        virtual void setKd(const double kd) {this->kd = kd;}
        virtual void setKs(const double ks) {this->ks = ks;}
        virtual void setKt(const double kt) {this->kt = kt;}
        virtual void setKl(const double kl) {this->kl = kl;}
        virtual void setRGB(const RGBColor &color) {this->color = color;}
        virtual void setMassPoints(list<shared_ptr<MassPoint>> &massPoints) {this->massPoints = massPoints;}
        virtual void setFaces(list<shared_ptr<PlaneFace>> &faces) {this->faces = faces;}
        virtual void setSphereCover(const SphereCover &cover) {this->cover = cover;}

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

        virtual bool getGrabbingPoint(Point &point, const Ray &ray) const;

        virtual double getKa() const {return ka;}
        virtual double getKd() const {return kd;}
        virtual double getKs() const {return ks;}
        virtual double getKt() const {return kt;}
        virtual double getKl() const {return kl;}
        virtual RGBColor getRGB() const {return color;}

        virtual bool isIntersected(const Ray &ray) const;
};

#endif
