#include "triangle.hh"
#include "../application.hh"

namespace x
{
    namespace graphics
    {
        namespace primitives
        {
            static void load(x::graphics::buffer & o)
            {
                o.target(x::graphics::buffer::array);
                o.usage(x::graphics::buffer::statical, x::graphics::buffer::draw);
            }

            static void load(x::graphics::vertices & o)
            {
                o.mode(x::graphics::vertices::triangle);

                o.push(x::graphics::vertex({ 0.0f, 1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}));
                o.push(x::graphics::vertex({ 1.0f,-1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}));
                o.push(x::graphics::vertex({-1.0f,-1.0f, 0.0f, 1.0f}, { 0.0f,  0.0f, 1.0f, 0.0f}));
            }

            triangle::triangle()
            :   x::graphics::primitive("triangle")
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::primitives::load(buffer);
                x::graphics::primitives::load(vertices);
            }

            triangle::triangle(const x::string & name)
            :   x::graphics::primitive(name)
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::primitives::load(buffer);
                x::graphics::primitives::load(vertices);
            }

            triangle::triangle(x::string && name)
            :   x::graphics::primitive(x::move(name))
            {
                x::graphics::application & application = x::graphics::application::get();

                x::graphics::primitives::load(buffer);
                x::graphics::primitives::load(vertices);
            }

            triangle::~triangle()
            {
            }
        }
    }
}
