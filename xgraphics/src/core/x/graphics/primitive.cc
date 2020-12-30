#include "primitive.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        primitive::primitive(const x::string & name)
        :   x::graphics::reference(),
            vertices(),
            buffer(),
            indices(),
            __name(name)
        {
        }

        primitive::primitive(x::string && name)
        :   x::graphics::reference(),
            vertices(),
            buffer(),
            indices(),
            __name(x::move(name))
        {
        }

        primitive::primitive()
        :   x::graphics::reference(),
            vertices(),
            buffer(),
            indices(),
            __name()
        {
        }

        primitive::primitive(const x::graphics::primitive & o)
        :   x::graphics::reference(),
            vertices(o.vertices),
            buffer(o.buffer),
            indices(o.indices),
            __name(o.__name)
        {
        }

        primitive::primitive(x::graphics::primitive && o) noexcept
        :   x::graphics::reference(),
            vertices(x::move(o.vertices)),
            buffer(x::move(o.buffer)),
            indices(x::move(o.indices)),
            __name(x::move(o.__name))
        {
        }

        primitive::~primitive()
        {
        }

        x::graphics::primitive & primitive::operator=(const x::graphics::primitive & o)
        {
            if(&o != this)
            {
                vertices = o.vertices;
                buffer = o.buffer;
                indices = o.indices;
                __name = o.__name;
            }
            return *this;
        }

        x::graphics::primitive & primitive::operator=(x::graphics::primitive && o) noexcept
        {
            if(&o != this)
            {
                vertices = x::move(o.vertices);
                buffer = x::move(o.buffer);
                indices = x::move(o.indices);
                __name = x::move(o.__name);
            }
            return *this;
        }

        const x::string & primitive::name() const
        {
            return __name;
        }

        void primitive::load()
        {
            x::graphics::application & application = x::graphics::application::get();

            application.load(*this);
        }

        void primitive::unload()
        {
            x::graphics::application & application = x::graphics::application::get();

            application.unload(*this);
        }

        void primitive::render()
        {
            x::graphics::application & application = x::graphics::application::get();

            application.bind(buffer);
            application.bind(0, 4, buffer, x::graphics::vertex::stride,  0 * sizeof(x::real));
            application.bind(1, 4, buffer, x::graphics::vertex::stride,  4 * sizeof(x::real));
            application.bind(2, 4, buffer, x::graphics::vertex::stride,  8 * sizeof(x::real));
            application.bind(3, 2, buffer, x::graphics::vertex::stride, 12 * sizeof(x::real));

            application.draw(vertices, indices);
        }
    }
}
