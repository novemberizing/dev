#include "direction.hh"

namespace x
{
    namespace physics
    {
        x::real direction::calculate(x::real value, x::real initial, x::real basis, x::real interval, x::real k)
        {
            if(initial <= basis)
            {
                x::real v = k * (x::atan(interval - 8) + x::pi / 2) * x::pi;
                value = value + v;
                return basis <= value ? basis : value;
            }
            else
            {
                x::real v = k * (x::atan(interval - 8) + x::pi / 2) * x::pi;
                value = value - v;
                return basis >= value ? basis : value;
            }
        }

        direction::direction(const x::reality::vector & direction)
        :   x::reality::variable<x::reality::vector>(direction),
            __k(0.01f)
        {
        }

        direction::direction()
        :   x::reality::variable<x::reality::vector>(),
            __k(0.01f)
        {
        }

        direction::direction(const x::physics::direction & o)
        :   x::reality::variable<x::reality::vector>(o),
            __k(o.__k)
        {
        }

        direction::direction(x::physics::direction && o) noexcept
        :   x::reality::variable<x::reality::vector>(x::move(o)),
            __k(o.__k)
        {
            o.__k = 0.01f;
        }

        direction::~direction()
        {
        }

        x::physics::direction & direction::operator=(const x::physics::direction & o)
        {
            if(&o != this)
            {
                x::reality::variable<x::reality::vector>::operator=(o);

                __k = o.__k;
            }
            return *this;
        }

        x::physics::direction & direction::operator=(x::physics::direction && o) noexcept
        {
            if(&o != this)
            {
                x::reality::variable<x::reality::vector>::operator=(x::move(o));

                __k = o.__k;

                o.__k = 0.01f;
            }
            return *this;
        }

        void direction::update()
        {
            if(__current != __value)
            {
                __interval = __interval + 1;
                if(__current.x() != __value.x())
                {
                    __current.x(direction::calculate(__current.x(), __initial.x(), __value.x(), __interval, __k));
                }
                if(__current.y() != __value.y())
                {
                    __current.y(direction::calculate(__current.y(), __initial.y(), __value.y(), __interval, __k));
                }
                if(__current.z() != __value.z())
                {
                    __current.z(direction::calculate(__current.z(), __initial.z(), __value.z(), __interval, __k));
                }
            }
            else
            {
                __interval = 0.0f;
            }
        }
    }
}
