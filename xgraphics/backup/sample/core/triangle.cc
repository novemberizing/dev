#include <x/graphics/opengl/application.hh>
#include <x/graphics/objects/simple.hh>

int main(int argc, char ** argv)
{
    // APPLICATION INITIALIZE
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);
    // CREATE LAYER
    application.add(new x::graphics::layer("main"));
    // CREATE OBJECT
    application.add(application.layer("main"), new x::graphics::objects::simple("triangle", application.reference("triangle"), application.program("simple"), nullptr));
    // DISPATCH LAYER IN THE SURFACE
    application.surface.dispatch(application.layer("main"));
    // RUN APPLICATION
    return application.run();
}
