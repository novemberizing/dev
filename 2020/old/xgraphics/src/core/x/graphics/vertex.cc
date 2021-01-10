#include "vertex.hh"

namespace x
{
    namespace graphics
    {
        vertex::vertex(const x::initializer<x::real> & location, const x::initializer<x::real> & normal, const x::initializer<x::real> & color, const x::initializer<x::real> & texture)
        :   __location(location),
            __normal(normal),
            __color(color),
            __texture(texture),
            __tangent(),
            __binormal()
        {
        }

        vertex::vertex(const x::initializer<x::real> & location, const x::initializer<x::real> & normal)
        :   __location(location),
            __normal(normal),
            __color(),
            __texture(),
            __tangent(),
            __binormal()
        {
        }

        vertex::vertex()
        :   __location(),
            __normal(),
            __color(),
            __texture(),
            __tangent(),
            __binormal()
        {
        }

        vertex::vertex(const vertex & o)
        :   __location(o.__location),
            __normal(o.__normal),
            __color(o.__color),
            __texture(o.__texture),
            __tangent(o.__tangent),
            __binormal(o.__binormal)
        {
        }

        vertex::vertex(vertex && o) noexcept
        :   __location(x::move(o.__location)),
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
                __location = o.__location;
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
                __location = x::move(o.__location);
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
