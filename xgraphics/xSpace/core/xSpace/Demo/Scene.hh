#ifndef   __X_SPACE_DEMO__SCENE__HH__
#define   __X_SPACE_DEMO__SCENE__HH__

#include <xSpace/Game/Scene.hh>

namespace xSpace
{
    namespace Demo
    {
        class Scene : public xSpace::Game::Scene
        {
        public:     Scene();
        public:     ~Scene() override;
        public:     xSpace::Demo::Scene & operator=(const xSpace::Demo::Scene & o) = delete;
        public:     xSpace::Demo::Scene & operator=(xSpace::Demo::Scene && o) noexcept = delete;
        public:     Scene(const xSpace::Demo::Scene & o) = delete;
        public:     Scene(xSpace::Demo::Scene && o) noexcept = delete;
        };
    }
}

#endif // __X_SPACE_DEMO__SCENE__HH__
