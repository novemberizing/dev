#include <x/graphics/vector.hh>
#include <x/console.hh>

using namespace x;

int main()
{
    {
        x::graphics::vector o;
        x::console::out << o << x::endl;
        x::console::out << o.x() << x::endl;
        o.x(1.0f);
        x::console::out << o.y() << x::endl;
        o.y(2.0f);
        x::console::out << o.z() << x::endl;
        o.z(3.0f);
        x::console::out << o.w() << x::endl;
        x::console::out << o << x::endl;
    }
    {
        x::graphics::vector source = { 1.0f, 2.0f, 3.0f, 4.0f };
        x::console::out << source << x::endl;
        source = { 5.0f, 6.0f };
        x::console::out << source << x::endl;
    }
    return 0;
}
