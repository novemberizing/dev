#ifndef   __X_SPACE_GAME__SCENE__HH__
#define   __X_SPACE_GAME__SCENE__HH__

#include <xSpace/Scene.hh>
#include <xSpace/Game/Layer/World.hh>

namespace xSpace
{
    namespace Game
    {
        class Scene : public xSpace::Scene
        {
        protected:  xSpace::Game::Layer::World * __world;
        public:     void add(x::graphics::layer * layer) override;
        public:     void add(xSpace::Object * object) override;
        public:     Scene(const x::string & name);
        public:     ~Scene() override;
        public:     xSpace::Game::Scene & operator=(const xSpace::Game::Scene & o) = delete;
        public:     xSpace::Game::Scene & operator=(xSpace::Game::Scene && o) noexcept = delete;
        public:     Scene() = delete;
        public:     Scene(const xSpace::Game::Scene & o) = delete;
        public:     Scene(xSpace::Game::Scene && o) noexcept = delete;
        };
    }
}

#endif // __X_SPACE_GAME__SCENE__HH__
