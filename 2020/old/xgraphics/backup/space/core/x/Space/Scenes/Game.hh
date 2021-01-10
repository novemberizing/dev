#ifndef   __X_SPACE_SCENES__GAME__HH__
#define   __X_SPACE_SCENES__GAME__HH__

#include <x/Space/Scene.hh>
#include <x/Space/Senario.hh>
#include <x/Space/Resource.hh>

#include <x/Space/Layers/Game.hh>
#include <x/Space/Layers/Front.hh>

#include <x/Space/Objects/Radar.hh>
#include <x/Space/Game/Me.hh>

namespace xSpace
{
    namespace Scenes
    {
        class Game : public xSpace::Scene
        {
        protected:  xSpace::Senario * __senario;
        protected:  xSpace::Layers::Front __front;
        protected:  xSpace::Layers::Game __game;
        protected:  xSpace::Objects::Radar * __radar;
        protected:  xSpace::Game::Me __me;
        protected:  xSpace::Object * __selected;
        public:     void keyboard(x::byte key, x::int32 x, x::int32 y) override;
        public:     void special(x::int32 key, x::int32 x, x::int32 y) override;
        public:     virtual void load(xSpace::Senario * senario, xSpace::Resource & resource);
        public:     xSpace::Scenes::Game & operator=(const xSpace::Scenes::Game & o) = delete;
        public:     xSpace::Scenes::Game & operator=(xSpace::Scenes::Game && o) noexcept = delete;
        public:     Game();
        public:     Game(const xSpace::Scenes::Game & o) = delete;
        public:     Game(xSpace::Scenes::Game && o) noexcept = delete;
        public:     ~Game() override;
        };
    }
}

#endif // __X_SPACE_SCENES__GAME__HH__
