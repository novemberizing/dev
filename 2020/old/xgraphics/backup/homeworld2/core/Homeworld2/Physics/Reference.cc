#include "Reference.hh"

namespace Homeworld2
{
    namespace Physics
    {
        // protected:  x::real __length;
        // protected:  x::real __width;
        // protected:  x::real __height;
        // protected:  x::real __mass;
        // protected:  x::real __energy;

        Reference::Reference(const x::string & name)
        :   x::reality::reference(name),
            x::physics::reference(),
            __length(0),
            __width(0),
            __height(0),
            __mass(0),
            __energy(0)
        {
        }

        Reference::Reference(x::string && name)
        :   x::reality::reference(x::move(name)),
            x::physics::reference(),
            __length(0),
            __width(0),
            __height(0),
            __mass(0),
            __energy(0)
        {
        }

        Reference::Reference(x::real weight, x::real energy)
        :   x::reality::reference(),
            x::physics::reference(),
            __length(0),
            __width(0),
            __height(0),
            __mass(weight),
            __energy(energy)
        {
        }

        Reference::Reference(const x::string & name, x::real weight, x::real energy)
        :   x::reality::reference(name),
            x::physics::reference(),
            __length(0),
            __width(0),
            __height(0),
            __mass(weight),
            __energy(energy)
        {
        }

        Reference::Reference(x::string && name, x::real weight, x::real energy)
        :   x::reality::reference(x::move(name)),
            x::physics::reference(),
            __length(0),
            __width(0),
            __height(0),
            __mass(weight),
            __energy(energy)
        {
        }

        Reference::Reference()
        :   x::reality::reference(),
            x::physics::reference(),
            __length(0),
            __width(0),
            __height(0),
            __mass(0),
            __energy(0)
        {
        }

        Reference::Reference(const Homeworld2::Physics::Reference & o)
        :   x::reality::reference(o),
            x::physics::reference(o),
            __length(o.__length),
            __width(o.__width),
            __height(o.__height),
            __mass(o.__mass),
            __energy(o.__energy)
        {
        }

        Reference::Reference(Homeworld2::Physics::Reference && o) noexcept
        :   x::reality::reference(x::move(o)),
            x::physics::reference(x::move(o)),
            __length(o.__length),
            __width(o.__width),
            __height(o.__height),
            __mass(o.__mass),
            __energy(o.__energy)
        {
            o.__length = 0;
            o.__width = 0;
            o.__height = 0;
            o.__mass = 0;
            o.__energy = 0;
        }

        Reference::~Reference()
        {
            __length = 0;
            __width = 0;
            __height = 0;
            __mass = 0;
            __energy = 0;
        }

        Homeworld2::Physics::Reference & Reference::operator=(const Homeworld2::Physics::Reference & o)
        {
            if(&o != this)
            {
                x::reality::reference::operator=(o);
                x::physics::reference::operator=(o);

                __length = o.__length;
                __width = o.__width;
                __height = o.__height;
                __mass = o.__mass;
                __energy = o.__energy;
            }
            return *this;
        }

        Homeworld2::Physics::Reference & Reference::operator=(Homeworld2::Physics::Reference && o) noexcept
        {
            if(&o != this)
            {
                x::reality::reference::operator=(x::move(o));
                x::physics::reference::operator=(x::move(o));

                __length = o.__length;
                __width = o.__width;
                __height = o.__height;
                __mass = o.__mass;
                __energy = o.__energy;

                o.__length = 0;
                o.__width = 0;
                o.__height = 0;
                o.__mass = 0;
                o.__energy = 0;

            }
            return *this;
        }

        const x::real Reference::weight() const
        {
            return __mass;
        }

        void Reference::weight(x::real v)
        {
            __mass = v;
        }

        const x::real Reference::energy() const
        {
            return __energy;
        }

        void Reference::energy(x::real v)
        {
            __energy = v;
        }
    }
}
