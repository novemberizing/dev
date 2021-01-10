#ifndef   __X_SPACE_SCENES__INTRO__HH__
#define   __X_SPACE_SCENES__INTRO__HH__

#include <x/Space/Scene.hh>

namespace xSpace
{
    namespace Scenes
    {
        class Intro : public xSpace::Scene
        {
        public:     xSpace::Scenes::Intro & operator=(const xSpace::Scenes::Intro & o) = delete;
        public:     xSpace::Scenes::Intro & operator=(xSpace::Scenes::Intro && o) noexcept = delete;
        public:     Intro();
        public:     Intro(const xSpace::Scenes::Intro & o) = delete;
        public:     Intro(xSpace::Scenes::Intro && o) noexcept = delete;
        public:     ~Intro() override;
        };
    }
}

#endif // __X_SPACE_SCENES__INTRO__HH__
