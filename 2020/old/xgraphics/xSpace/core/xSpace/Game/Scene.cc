#include "Scene.hh"

namespace xSpace
{
    namespace Game
    {
        Scene::Scene(const x::string & name)
        :   xSpace::Scene(name),
            __world(nullptr)
        {
            __world = new xSpace::Game::Layer::World();

            add(__world);
        }

        Scene::~Scene()
        {
        }

        void Scene::add(x::graphics::layer * layer)
        {
            layers.append(layer);
        }

        void Scene::add(xSpace::Object * object)
        {
            __objects.append(object);

            __world->add(object);
        }
    }
}
