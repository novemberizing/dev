#include <x/graphics/opengl/application.hh>

int main(int argc, char ** argv)
{
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);

    // CREATE LAYER
    x::graphics::layer * layer = new x::graphics::layer("layer");

    // CREATE OBJECT
    x::graphics::object * triangle = new x::graphics::object("triangle", x::reality::vector::center, x::reality::vector::front, x::reality::vector::up ,application.reference("triangle"), application.program("simple"));

    // ADD OBJECT IN THE LAYER
    layer->add(triangle);

    // DISPATCH LAYER
    application.surface.dispatch(layer);

    return application.run();
}
