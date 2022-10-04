#ifndef CAMERA_H
#define CAMERA_H

#include "object.hpp"

class Camera: public Object
{
    private:
        Point pos;
        Vector3d viewVector;

    public:
        Camera() = default;
        Camera(const Point &pos, const Vector3d &viewVector)
        {
            this->pos = pos;
            this->viewVector = viewVector;
        }

        virtual ~Camera() = default;

        virtual void update(const size_t ms) {return;}

        virtual void move(
            const double dx,
            const double dy,
            const double dz
        );
        virtual void rotate(
            const double xAngle,
            const double yAngle,
            const double zAngle
        );

        virtual void setMass(const double mass) {return;}
        virtual void setStiffness(const double k) {return;}
        virtual void setKd(const double kd) {return;}
        virtual void setKs(const double ks) {return;}
        virtual void setKt(const double kt) {return;}
        virtual void setPos(
            const double x,
            const double y,
            const double z
        );
        virtual void setRGB(
            const short unsigned r,
            const short unsigned g,
            const short unsigned b
        ) {return;};
        virtual void setIntensity(const double i) {return;}
        virtual void setMassPoints(List<shared_ptr<MassPoints>> &massPoints) {return;}
        virtual void setFaces(List<shared_ptr<PlaneFace>> &faces) {return;}

        virtual pair<Point, RGBColor> getIntersection(const Ray &ray);  // Надо вернуть "пустую пару" или что-то в этом роде
        virtual shared_ptr<PlaneFace> getIntersectedPlane(const Ray &ray) {return nullptr;} // и тутт тоже

        virtual double getKd() {return;}
        virtual double getKs() {return;}
        virtual double getKt() {return;}
        virtual RGBColor getRGB() {return RGBColor(0, 0, 0);}
        virtual Point getPos() {return pos;}
        virtual double getIntensity() {return 0.0;}
};

#endif
