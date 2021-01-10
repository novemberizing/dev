#include <Homeworld2/Resource.hh>

#include <Homeworld2/Graphics/ReferenceFile.hh>
#include <Homeworld2/Units/Ship.hh>

#include <x/io/event/generator/epoll.hh>
#include <x/graphics/opengl/application.hh>
#include <x/graphics/shader.hh>
#include <x/graphics/program.hh>
#include <x/graphics/images/bitmap.hh>
#include <x/graphics/primitives/image.hh>

#include <x/graphics/images/dds.hh>


static x::graphics::program load(const x::string & name, const x::string & vertexPath, const x::string & fragmentPath, const x::initializer<x::string> & uniforms);
static Homeworld2::Graphics::Reference * load(const x::string & path, const x::string & name);

int main(int argc, char ** argv)
{
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);
    // FOR DEBUG
    x::graphics::images::bitmap o = x::graphics::images::bitmap::load("/home/sean/Workspace/discomplexity/xgraphics/res/texture/check.pattern.bmp");
    application.add(o.build("check pattern"));
    application.add(new x::graphics::primitives::image("bottom", &application.textures["check pattern"],{100000.0f, 100000.0f, 1.0f}, {90.0f, 0.0f, 0.0f}, 1000));
    application.surface.add(new x::graphics::object("bottom", {0.0f, -300.0f, 0.0f, 1.0f}, application.references["bottom"]));
    application.surface.add(new x::graphics::object("top", {0.0f, 300.0f, 0.0f, 1.0f}, application.references["bottom"]));
    // FOR DEBUG

    Homeworld2::Resource & resource = Homeworld2::Resource::init("/home/sean/Workspace/discomplexity/xgraphics/homeworld2/res");

    resource.load();

    return 0;




    Homeworld2::Graphics::Reference * gundam = load("sample3.hod", "sample3");

    application.add(load("sample1.hod", "sample1"));
    application.add(load("sample2.hod", "sample2"));
    application.add(load("sample2.hod", "sample2"));
    application.add(gundam);




    Homeworld2::Units::Ship * ship = new Homeworld2::Units::Ship("main", {0.0f, 0.0f, 0.0f, 1.0f}, 1000.0f, {0.0f, 0.0f, 0.0f}, gundam->build());
    x::console::out << "virtual name => " << ship->name() << x::endl;
    application.surface.add(ship);

    application.camera(ship->camera());


    application.keyboard([&application, ship](unsigned char key, int x, int y){
        switch(key)
        {
            case 'a': ship->force(1.0f);    break;
            case 'z': ship->force(-1.0f);   break;
            case 'q': {
                          if(&application.camera() == ship->camera())
                          {
                              application.camera(nullptr);
                          }
                          else
                          {
                              application.camera(ship->camera());
                          }
                      }
                      break;
            case 'w': {
                          ship->__camera.category(ship->__camera.category() + 1);
                          // const x::reality::camera & camera = application.camera();
                          // camera.view()
                      }
                      break;
            case 'e': {
                          ship->__camera.direction(ship->__camera.direction() + 1);
                      }
                      break;
            default:                        break;
        }
    });

    application.special([ship](int key, int x, int y){
        switch(key)
        {
            case x::keyboard::up: ship->direction(x::reality::vector::radian({0.0f, 0.0f, 5.0f}));    break;
            case x::keyboard::down: ship->direction(x::reality::vector::radian({0.0f, 0.0f, -5.0f}));   break;
            case x::keyboard::left: ship->direction(x::reality::vector::radian({0.0f, 5.0f, 0.0f}));    break;
            case x::keyboard::right: ship->direction(x::reality::vector::radian({0.0f, -5.0f, 0.0f}));   break;
            case x::keyboard::top: ship->direction(x::reality::vector::radian({5.0f, 0.0f, 0.0f}));    break;
            case x::keyboard::bottom: ship->direction(x::reality::vector::radian({-5.0f, 0.0f, 0.0f}));   break;
            default:                        break;
        }
    });

    application.engine.add(new x::io::event::generator::epoll(application.engine));
    application.engine.add(x::event::type::io, x::console::out);
    application.engine.add(x::event::type::io, x::console::in);

    x::console::out.off();
    x::console::in.set([](const x::string & o) {
        x::console::out.flush();
        x::graphics::application & application = x::graphics::application::get();
        x::array<x::string> strings = o.split('\n');
        for(x::uint64 i = 0; i < strings.size(); i++)
        {
            // application.exec(strings[i]);
        }
        x::console::out.flush();
    });

    return application.run();
}

Homeworld2::Graphics::Reference * load(const x::string & file, const x::string & name)
{
    x::string path = "/home/sean/Workspace/discomplexity/xgraphics/res/ship/" + file;
    return Homeworld2::Graphics::ReferenceFile::load(path, name);
}

x::graphics::program load(const x::string & name, const x::string & vertexPath, const x::string & fragmentPath, const x::initializer<x::string> & uniforms)
{
    x::string path = "";

    path = "/home/sean/Workspace/discomplexity/xgraphics/res/shader/homeworld2/ship/" + vertexPath;
    x::graphics::shader vertex(name + " vertex shader", x::graphics::shader::vertex, x::file::text(path));

    path = "/home/sean/Workspace/discomplexity/xgraphics/res/shader/homeworld2/ship/" + fragmentPath;
    x::graphics::shader fragment(name + " fragment shader", x::graphics::shader::fragment, x::file::text(path));

    x::graphics::program program(name, uniforms);

    program.add(vertex);
    program.add(fragment);

    return program;
}
