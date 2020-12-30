#include <x/graphics/opengl/application.hh>

#include <Homeworld2/Resource.hh>
#include <Homeworld2/Senario.hh>
#include <Homeworld2/Graphics/Reference.hh>

int main(int argc, char ** argv)
{
    // RETRIEVE GLOBAL INSTANCE
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv, nullptr);
    Homeworld2::Resource & resource = Homeworld2::Resource::get();

    // DEBUG(ONLY) START
    // application.environment.root(x::directory::current(argv[0] + x::string("/../../../../..")) + "/homeworld2");
    application.environment.root("/home/sean/Workspace/discomplexity/xgraphics/homeworld2");
    // DEBUG(ONLY) END

    // LOAD HOMEWORLD2 RESOURCE
    resource.load(application);

    Homeworld2::Senario * senario = Homeworld2::Senario::open("demo", resource);


    // CREATE OBJECT
    // Homeworld2::Graphics::Objects::Root * sample = homeworld2.build("sample", "zephyranthes", nullptr, 0, x::reality::vector::center, x::reality::vector::front, x::reality::vector::up);
    // Homeworld2::Graphics::Objects::Root * sample = homeworld2.build("sample", "rgm79c", nullptr, 0, x::reality::vector::center, x::reality::vector::front, x::reality::vector::up);
    // Homeworld2::Graphics::Objects::Root * sample = homeworld2.build("sample", "msm05", nullptr, 0, x::reality::vector::center, x::reality::vector::front, x::reality::vector::up);
    Homeworld2::Graphics::Objects::Root * sample = resource.build("sample", "salamis", nullptr, 0, x::reality::vector::center, x::reality::vector::front, x::reality::vector::up);

    // CREATE LAYER
    x::graphics::layer * layer = new x::graphics::layer("demo");
    layer->add(sample);

    // DISPATCH WORLD & FRONT
    // application.surface.dispatch(layer);

    return application.run();
}
