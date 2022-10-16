#include "scene.hpp"

Scene::Scene(
    const shared_ptr<Object> &camera, const shared_ptr<Object> &lightSource,
    const shared_ptr<Object> &slime, const shared_ptr<Object> &floor
)
{
    this->camera = camera;
    this->lightSource = lightSource;
    this->slime = slime;
    this-> floor = floor;
}
