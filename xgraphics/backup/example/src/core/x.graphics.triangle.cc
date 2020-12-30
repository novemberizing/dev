#include <x/graphics/opengl/application.hh>
#include <x/graphics/primitives/triangle.hh>

int main(int argc, char ** argv)
{
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);

    application.surface.add(new x::graphics::object("main", {0.0f, 0.0f, 0.0f}, application.references["triangle"]));

    return application.run();
}
