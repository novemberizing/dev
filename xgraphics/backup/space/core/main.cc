#include <x/graphics/opengl/application.hh>

#include <x/Space/Application.hh>

int main(int argc, char ** argv)
{
    // INITIALIZE OPENGL APPLICATION
    xSpace::Application & application = xSpace::Application::init(x::graphics::opengl::application::init(argc, argv, [](x::graphics::application & application){
        application.width(1024);
        application.height(768);
        application.environment.root("/home/novemberizing/Workspace/discomplexity/xgraphics/space"); // for debug
    }));

    // application
    // LOAD SPACE RESOURCE

    // GET DEMO SENARIO
    // xSpace::Senario * senario = resource.senario("demo");


    // // LOAD HOMEWORLD2 RESOURCE
    // Homeworld2::Resource resource = Homeworld2::Resource::get();
    // resource.load(application);

    // RUN OPENGL APPLICATION
    return application.run();
}
