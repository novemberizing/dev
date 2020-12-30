#include "Scene.hh"

namespace xSpace
{
    Scene::Scene()
    :   x::graphics::surface()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::keyboard(x::byte key, x::int32 x, x::int32 y)
    {
        x::console::out << "keyboard => " << key << x::endl << x::flush;
    }

    void Scene::special(x::int32 key, x::int32 x, x::int32 y)
    {
        x::console::out << "special => " << key << x::endl << x::flush;
    }
}
