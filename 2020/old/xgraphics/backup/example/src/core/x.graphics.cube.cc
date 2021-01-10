#include <x/graphics/opengl/application.hh>
#include <x/graphics/primitives/cube.hh>

int main(int argc, char ** argv)
{
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);

    application.surface.add(new x::graphics::object("main", {0.0f, 0.0f, 0.0f}, application.references["cube"]));
    // x::graphics::surface & surface = application.surface();
    // // add prebuilt graphics object
    // application.add(new x::graphics::primitives::cube());
    // // add surface graphics reference ..
    // surface.add("main", application.object("cube"), {0.0f, 0.0f, 0.0f, 1.0f});

    return application.run();
}
