#ifndef   __X_SPACE__APPLICATION__HH__
#define   __X_SPACE__APPLICATION__HH__

#include <x/graphics/application.hh>

#include <x/Space/Resource.hh>
#include <x/Space/Scenes/Game.hh>
#include <x/Space/Scenes/Intro.hh>
#include <x/Space/Scenes/Lobby.hh>

namespace xSpace
{
    class Application
    {
    protected:  static xSpace::Application * __singleton;
    public:     static xSpace::Application & init(x::graphics::application & application);
    public:     static xSpace::Application & get(){ return *__singleton; }
    protected:  x::graphics::application & __application;
    protected:  xSpace::Resource & __resource;
    protected:  xSpace::Senario * __senario;
    protected:  xSpace::Scenes::Intro __intro;
    protected:  xSpace::Scenes::Lobby __lobby;
    protected:  xSpace::Scenes::Game __game;
    protected:  xSpace::Scene * __current;
    public:     virtual void keyboard(x::byte key, x::int32 x, x::int32 y);
    public:     virtual void special(x::int32 key, x::int32 x, x::int32 y);
    public:     virtual x::int32 run();
    public:     xSpace::Application & operator=(const xSpace::Application & o) = delete;
    public:     xSpace::Application & operator=(xSpace::Application && o) noexcept = delete;
    protected:  Application(x::graphics::application & application, xSpace::Resource & resource);
    public:     Application() = delete;
    public:     Application(const xSpace::Application & o) = delete;
    public:     Application(xSpace::Application && o) noexcept = delete;
    public:     virtual ~Application();
    };
}

#endif // __X_SPACE__APPLICATION__HH__
