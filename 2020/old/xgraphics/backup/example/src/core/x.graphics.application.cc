#include <x/graphics/opengl/application.hh>

int main(int argc, char ** argv)
{
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);
    return application.run();
}
