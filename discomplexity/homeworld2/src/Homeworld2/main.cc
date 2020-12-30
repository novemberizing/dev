#include <x/graphics/opengl/application.hh>
#include <x/graphics/objects/cube.hh>
#include <x/io/event/generator/epoll.hh>
#include <Homeworld2/ObjectFile.hh>

int main(int argc, char ** argv)
{
    // x::graphics::matrix view = x::graphics::matrix::lookat(x::graphics::vector({4.0, 3.0, 3.0}),
    //                                                        x::graphics::vector({0.0, 0.0, 0.0}),
    //                                                        x::graphics::vector({0.0, 1.0, 0.0}));
    //
    // x::console::out << view << x::endl;
    // x::console::out << (x::graphics::vector({0.0, 0.0, 0.0}) - x::graphics::vector({4.0, 3.0, 3.0})) << x::endl;
    // x::console::out << x::graphics::matrix::perspective(0.7853981633974483f, 1.0380952380952382f, 0.1f, 1000.0f) << x::endl;
    //
    // x::graphics::matrix projection = x::graphics::matrix::perspective(0.7853981633974483f, 1.0380952380952382f, 0.1f, 1000.0f);
    // x::graphics::matrix model = x::graphics::matrix::identity();
    //
    // x::console::out << (projection * view * model) << x::endl;
    // x::console::out << x::graphics::matrix::rotate(x::graphics::matrix::identity(), x::math::radian(45.0),  x::graphics::vector({0.0, 1.0, 0.0})) << x::endl;

    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);

    Homeworld2::Object * object = Homeworld2::ObjectFile::load("/home/discomplexity/Workspace/discomplexity/discomplexity/sample.hod", "sample");

    application.add(object);
    application.add(x::graphics::reference("sample", object));

    x::event::engine & engine = application.engine();
    engine.add(new x::io::event::generator::epoll());
    engine.add(x::event::generator::type::io, x::console::out);
    engine.add(x::event::generator::type::io, x::console::in);

    x::console::out.off();

    x::console::in.set([](const x::string & o) {
        x::console::out.flush();
        x::graphics::application & application = x::graphics::application::get();
        x::array<x::string> strings = o.split('\n');
        for(x::uint64 i = 0; i < strings.size(); i++)
        {
            application.exec(strings[i]);
        }
        x::console::out.flush();
    });



    return application.run();
}
