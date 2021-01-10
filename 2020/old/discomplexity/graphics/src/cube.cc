#include <x/graphics/opengl/application.hh>
#include <x/graphics/objects/cube.hh>
#include <x/io/event/generator/epoll.hh>

int main(int argc, char ** argv)
{
    x::graphics::application & application = x::graphics::opengl::application::init(argc, argv);
    // load object
    application.add(new x::graphics::objects::cube("cube"));
    // init graphics reference
    x::graphics::surface & surface = application.surface();

    surface.add("cube", application.object("cube"));
    // application.surface()
    // application.surface();

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
