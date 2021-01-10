#ifndef   __X_SPACE__APPLICATION__HH__
#define   __X_SPACE__APPLICATION__HH__

#include <x/graphics/application.hh>

#include <xSpace/Resource.hh>
#include <xSpace/Scene.hh>
#include <xSpace/Demo/Scene.hh>

namespace xSpace
{
    class Application
    {
    protected:  static xSpace::Application * __singleton;
    public:     static xSpace::Application & init(int argc, char ** argv);
    public:     static xSpace::Application & get();
    protected:  x::graphics::application & __graphics;
    protected:  xSpace::Scene * __current;
    protected:  x::map<x::string, xSpace::Scene *> __scenes;
    public:     virtual x::int32 run();
    protected:  Application(x::graphics::application & graphics);
    public:     virtual ~Application();
    public:     Application() = delete;
    public:     Application(const xSpace::Application & o) = delete;
    public:     Application(xSpace::Application && o) noexcept = delete;
    public:     xSpace::Application & operator=(const xSpace::Application & o) = delete;
    public:     xSpace::Application & operator=(xSpace::Application && o) noexcept = delete;
    };
}

#endif // __X_SPACE__APPLICATION__HH__
