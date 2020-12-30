#ifndef   __X_SPACE_SCENES__LOBBY__HH__
#define   __X_SPACE_SCENES__LOBBY__HH__

#include <x/Space/Scene.hh>

namespace xSpace
{
    namespace Scenes
    {
        class Lobby : public xSpace::Scene
        {
        public:     xSpace::Scenes::Lobby & operator=(const xSpace::Scenes::Lobby & o) = delete;
        public:     xSpace::Scenes::Lobby & operator=(xSpace::Scenes::Lobby && o) noexcept = delete;
        public:     Lobby();
        public:     Lobby(const xSpace::Scenes::Lobby & o) = delete;
        public:     Lobby(xSpace::Scenes::Lobby && o) noexcept = delete;
        public:     ~Lobby() override;
        };
    }
}

#endif // __X_SPACE_SCENES__LOBBY__HH__
