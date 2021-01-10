#include "Application.hh"

#include <x/graphics/opengl/application.hh>

namespace xSpace
{
    xSpace::Application * xSpace::Application::__singleton = nullptr;

    xSpace::Application & Application::init(int argc, char ** argv)
    {
        if(__singleton == nullptr)
        {
            static xSpace::Application o(x::graphics::opengl::application::init(argc, argv, [](x::graphics::application & application){
                application.width(1024);
                application.height(768);
                application.environment.root("/home/sean/Workspace/discomplexity/xgraphics/xSpace");
            }));

            xSpace::Resource & resource = xSpace::Resource::get();

            resource.load(o.__graphics);

            // DEMO
            xSpace::Demo::Scene * demo = resource.demo();

            o.__scenes.put(demo->name(), demo);
            o.__current = demo;
            o.__graphics.surface(o.__current);

            __singleton = &o;
        }
        return *__singleton;
    }

    xSpace::Application & Application::get()
    {
        assertion(__singleton == nullptr);

        return *__singleton;
    }

    Application::Application(x::graphics::application & graphics)
    :   __graphics(graphics),
        __current(nullptr),
        __scenes()
    {

    }

    Application::~Application()
    {

    }

    x::int32 Application::run()
    {
        return __graphics.run();
    }
}
