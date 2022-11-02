#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "spherecover.hpp"
#include "lightsource.hpp"
#include "planeface.hpp"
#include "camera.hpp"
#include "slime.hpp"
#include "floor.hpp"

using namespace std;

class Plot;

class Scene
{
    friend class Plot;

    private:
        shared_ptr<Object> camera;
        shared_ptr<Object> lightSource;
        shared_ptr<Object> slime;
        shared_ptr<Object> floor;

    public:
        Scene() = default;
        Scene(
            const shared_ptr<Object> &camera, const shared_ptr<Object> &lightSource,
            const shared_ptr<Object> &slime, const shared_ptr<Object> &floor
        );

        virtual ~Scene() = default;

        // virtual void update(const size_t ms) {slime->update(ms);}

        // virtual shared_ptr<Object> getCamera() {return camera;}
        // virtual shared_ptr<Object> getLightSource() {return lightSource;}
        // virtual shared_ptr<Object> getSlime() {return slime;}
        // virtual shared_ptr<Object> getFloor() {return floor;}

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
        
        virtual bool isIntersected(const Ray &ray) const;
};

#endif
