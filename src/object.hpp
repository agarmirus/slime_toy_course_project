#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include <memory>

#include "planeface.hpp"
#include "masspoint.hpp"
#include "rgbcolor.hpp"
#include "point.hpp"
#include "ray.hpp"

using namespace std;

class Object
{
    public:
        virtual ~Object() = default;

        virtual void update(const size_t ms) = 0;
        virtual void updateCover() {return;}

        virtual void setMass(const double mass) {return;}
        virtual void setStiffness(const double k) {return;}
        virtual void setDamp(const double kdmp) {return;}
        virtual void setKa(const double ka) {return;}
        virtual void setKd(const double kd) {return;}
        virtual void setKs(const double ks) {return;}
        virtual void setKt(const double kt) {return;}
        virtual void setKl(const double kl) {return;}
        virtual void setPos(const Point &pos) {return;}
        virtual void setVec(const Vector3d &vec) {return;}
        virtual void setRGB(const RGBColor &color) {return;}
        virtual void setMassPoints(list<shared_ptr<MassPoint>> &massPoints) {return;}
        virtual void setFaces(list<shared_ptr<PlaneFace>> &faces) {return;}

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
        ) const {return false;}

        virtual shared_ptr<Point> getGrabbingPoint(const Ray &ray) const {return nullptr;}

        virtual double getKa() const {return 0.0;}
        virtual double getKd() const {return 0.0;}
        virtual double getKs() const {return 0.0;}
        virtual double getKt() const {return 0.0;}
        virtual double getKl() const {return 0.0;}
        virtual RGBColor getRGB() const {return RGBColor(0, 0, 0);}
        virtual Point getPos() const {return Point(0.0, 0.0, 0.0);}
        virtual Vector3d getVec() const {return Vector3d();}

        virtual void turnAroundOZ(const double angle) {return;}
        virtual void turnAroundOY(const double angle) {return;}
        virtual void turnAroundOX(const double angle) {return;}

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        ) {return;}

        virtual void toViewport(Vector3d &vec) {return;}

        virtual bool isIntersected(const Ray &ray) const {return false;}
};

#endif
