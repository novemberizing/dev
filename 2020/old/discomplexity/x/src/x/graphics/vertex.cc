#include "vertex.hh"

namespace x
{
    namespace graphics
    {
        vertex::vertex(const x::initializer<x::float32> & position, const x::initializer<x::float32> & normal)
        :   __position(position),
            __normal(normal),
            __color(),
            __texture(),
            __tangent(),
            __binormal()
        {
        }
        
        vertex::vertex()
        :   __position(),
            __normal(),
            __color(),
            __texture(),
            __tangent(),
            __binormal()
        {
        }

        vertex::vertex(const vertex & o)
        :   __position(o.__position),
            __normal(o.__normal),
            __color(o.__color),
            __texture(o.__texture),
            __tangent(o.__tangent),
            __binormal(o.__binormal)
        {
        }

        vertex::vertex(vertex && o) noexcept
        :   __position(x::move(o.__position)),
            __normal(x::move(o.__normal)),
            __color(x::move(o.__color)),
            __texture(x::move(o.__texture)),
            __tangent(x::move(o.__tangent)),
            __binormal(x::move(o.__binormal))
        {
        }

        vertex::~vertex()
        {
        }

        vertex & vertex::operator=(const vertex & o)
        {
            if(&o != this)
            {
                __position = o.__position;
                __normal = o.__normal;
                __color = o.__color;
                __texture = o.__texture;
                __tangent = o.__tangent;
                __binormal = o.__binormal;
            }
            return *this;
        }

        vertex & vertex::operator=(vertex && o) noexcept
        {
            if(&o != this)
            {
                __position = x::move(o.__position);
                __normal = x::move(o.__normal);
                __color = x::move(o.__color);
                __texture = x::move(o.__texture);
                __tangent = x::move(o.__tangent);
                __binormal = x::move(o.__binormal);
            }
            return *this;
        }
    }
}
