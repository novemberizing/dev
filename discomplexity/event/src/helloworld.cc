#include <x/console.hh>
#include <x/event.hh>
#include <x/io/event/generator/epoll.hh>

int main()
{
    x::event::engine engine;

    engine.add(new x::io::event::generator::epoll());

    engine.add(x::event::generator::type::io, x::console::out);
    engine.add(x::event::generator::type::io, x::console::in);

    x::console::out.off();
    x::console::in.set([](const x::string & o){
        x::console::out << o;
    });
    return engine.run();
}
