#ifndef PLANEFACE_H
#define PLANEFACE_H

#include <memory>

#include "ray.hpp"
#include "point.hpp"
#include "vector3d.hpp"
#include "doubleop.hpp"

using namespace std;

class PlaneFace
{
    private:
        shared_ptr<Point> points[3];

        double coeffs[4];
    
    public:
        PlaneFace(
            const shared_ptr<Point> &p1,
            const shared_ptr<Point> &p2,
            const shared_ptr<Point> &p3
        );

        virtual ~PlaneFace() = default;

        virtual void updateCoefs();

        virtual Vector3d getNormal() const
        {
            return Vector3d(coeffs[0], coeffs[1], coeffs[2]);
        }

        virtual bool getIntersectionPoint(Point &point, const Ray &ray) const;
};

#endif
