#include "Application.hh"

namespace xSpace
{
    xSpace::Application * xSpace::Application::__singleton = nullptr;

    xSpace::Application & Application::init(x::graphics::application & application)
    {
        if(__singleton == nullptr)
        {
            xSpace::Resource & resource = xSpace::Resource::init(application);

            static xSpace::Application o(application, resource);

            // FOR DEMO
            o.__resource.load(application);
            o.__senario = resource.senario("demo");
            o.__game.load(o.__senario, o.__resource);

            application.surface(&o.__game);
            o.__current = &o.__game;

            __singleton = &o;
        }

        return *__singleton;
    }

    Application::Application(x::graphics::application & application, xSpace::Resource & resource)
    :   __application(application),
        __resource(resource),
        __senario(nullptr),
        __intro(),
        __lobby(),
        __game(),
        __current(nullptr)
    {
        application.surface(&__intro);
        __current = &__intro;

        application.keyboard([](unsigned char key, int x, int y){
            Application & application = Application::get();
            application.keyboard(key, x, y);
        });

        application.special([](unsigned char key, int x, int y){
            Application & application = Application::get();
            application.special(key, x, y);
        });
    }

    Application::~Application()
    {
    }

    x::int32 Application::run()
    {
        return __application.run();
    }

    void Application::keyboard(x::byte key, x::int32 x, x::int32 y)
    {
        if(__current)
        {
            __current->keyboard(key, x, y);
        }
    }

    void Application::special(x::int32 key, x::int32 x, x::int32 y)
    {
        if(__current)
        {
            __current->special(key, x, y);
        }
    }
}
