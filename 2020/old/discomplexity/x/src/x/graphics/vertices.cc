#include "vertices.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        vertices::vertices()
        :   __mode(x::graphics::vertices::none),
            __type(x::graphics::vertices::none),
            __adjacency(x::graphics::vertices::none),
            __id(0),
            __vertices()
        {
        }

        vertices::vertices(const vertices & o)
        :   __mode(o.__mode),
            __type(o.__type),
            __adjacency(o.__adjacency),
            __id(o.__id),
            __vertices(o.__vertices)
        {
        }

        vertices::vertices(vertices && o) noexcept
        :   __mode(o.__mode),
            __type(o.__type),
            __adjacency(o.__adjacency),
            __id(o.__id),
            __vertices(x::move(o.__vertices))
        {
            o.__mode = x::graphics::vertices::none;
            o.__type = x::graphics::vertices::none;
            o.__adjacency = x::graphics::vertices::none;
            o.__id = 0;
        }

        vertices::~vertices()
        {
        }

        vertices & vertices::operator=(const vertices & o)
        {
            if(&o != this)
            {
                __mode = o.__mode;
                __type = o.__type;
                __adjacency = o.__adjacency;
                __id = o.__id;
                __vertices = o.__vertices;
            }
            return *this;
        }

        vertices & vertices::operator=(vertices && o) noexcept
        {
            if(&o != this)
            {
                __mode = o.__mode;
                __type = o.__type;
                __adjacency = o.__adjacency;
                __id = o.__id;
                __vertices = x::move(o.__vertices);

                o.__mode = x::graphics::vertices::none;
                o.__type = x::graphics::vertices::none;
                o.__adjacency = x::graphics::vertices::none;
                o.__id = 0;
            }
            return *this;
        }

        void vertices::serialize(x::graphics::buffer & buffer) const
        {
            if(buffer.size() == 0)
            {
                for(x::uint64 i = 0; i < __vertices.size(); i++)
                {
                    const x::graphics::vertex & vertex = __vertices[i];
                    buffer.push(vertex.position());
                    buffer.push(vertex.normal());
                    buffer.push(vertex.color());
                    buffer.push(vertex.texture());
                    buffer.push(vertex.tangent());
                    buffer.push(vertex.binormal());
                }
                // x::console::out << "buffer size => " << buffer.size() << x::endl;
            }
        }
    }
}
