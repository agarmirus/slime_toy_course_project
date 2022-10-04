#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "camera.hpp"
#include "lightsource.hpp"
#include "slime.hpp"
#include "floor.hpp"

using namespace std;

class Scene
{
    private:
        shared_ptr<Object> camera;
        shared_ptr<Object> lightSource;
        shared_ptr<Object> slime;
        shared_ptr<Object> floor;

    public:
        Scene() = default;
        Scene(
            shared_ptr<Object> camera, shared_ptr<Object> lightSource,
            shared_ptr<Object> slime, shared_ptr<Object> floor
        ) {
            this->camera = camera;
            this->lightSource = lightSource;
            this->slime = slime;
            this->floor = floor;
        }

        virtual ~Scene() = default;

        virtual void update(const size_t ms);

        virtual shared_ptr<Object> getCamera() {return camera;}
        virtual shared_ptr<Object> getLightSource() {return lightSource;}
        virtual shared_ptr<Object> getSlime() {return slime;}
        virtual shared_ptr<Object> getFloor() {return floor;}
};

#endif
