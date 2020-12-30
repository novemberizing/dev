#ifndef   __X_SPACE_GAME_LAYER__WORLD__HH__
#define   __X_SPACE_GAME_LAYER__WORLD__HH__

#include <xSpace/Layer.hh>

namespace xSpace
{
    namespace Game
    {
        namespace Layer
        {
            class World : public xSpace::Layer
            {
            public:     World();
            public:     virtual ~World();
            public:     xSpace::Game::Layer::World & operator=(const xSpace::Game::Layer::World & o) = delete;
            public:     xSpace::Game::Layer::World & operator=(xSpace::Game::Layer::World && o) noexcept = delete;
            public:     World(const xSpace::Game::Layer::World & o) = delete;
            public:     World(xSpace::Game::Layer::World && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_SPACE_GAME_LAYER__WORLD__HH__
