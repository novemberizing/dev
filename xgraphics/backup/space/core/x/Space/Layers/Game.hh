#ifndef   __X_SPACE_LAYERS__GAME__HH__
#define   __X_SPACE_LAYERS__GAME__HH__

#include <x/graphics/layer.hh>

namespace xSpace
{
    namespace Layers
    {
        class Game : public x::graphics::layer
        {
        public:     xSpace::Layers::Game & operator=(const xSpace::Layers::Game & o) = delete;
        public:     xSpace::Layers::Game & operator=(xSpace::Layers::Game && o) noexcept = delete;
        public:     Game(const x::string & name);
        public:     Game() = delete;
        public:     Game(const xSpace::Layers::Game & o) = delete;
        public:     Game(xSpace::Layers::Game && o) noexcept = delete;
        public:     ~Game() override;
        };
    }
}

#endif // __X_SPACE_LAYERS__GAME__HH__
