#include "Scene.hh"

namespace xSpace
{
    Scene::Scene(const x::string & name)
    :   x::graphics::surface(),
        __name(name),
        __objects()
    {
    }

    Scene::Scene()
    :   x::graphics::surface(),
        __name(),
        __objects()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::add(xSpace::Object * object)
    {
        __objects.append(object);
    }

    void Scene::add(x::graphics::layer * layer)
    {
        layers.append(layer);
    }
}
