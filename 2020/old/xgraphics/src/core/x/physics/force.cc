#include "force.hh"
#include "friction.hh"

namespace x
{
    namespace physics
    {
        x::real force::calculate(x::real value, x::real initial, x::real basis, x::real interval, x::real k)
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

        x::real force::acceleration(x::real f, x::real m, x::real velocity)
        {
            // x::console::out << "force => " << f << x::endl << x::flush;
            // x::console::out << "velocity => " << velocity << x::endl << x::flush;
            return (f - friction::calculate(velocity)) / m;
        }

        x::real force::acceleration(x::real f, x::real m)
        {
            return f/m;
        }

        force::force()
        :   x::reality::variable<x::real>(),
            __k(0.01f)
        {
        }

        force::force(const x::physics::force & o)
        :   x::reality::variable<x::real>(o),
            __k(o.__k)
        {
        }

        force::force(x::physics::force && o) noexcept
        :   x::reality::variable<x::real>(x::move(o)),
            __k(o.__k)
        {
            o.__k = 0.01f;
        }

        force::~force()
        {
            __k = 0.01f;
        }

        x::physics::force & force::operator=(const x::physics::force & o)
        {
            if(&o != this)
            {
                x::reality::variable<x::real>::operator=(x::move(o));

                __k = o.__k;
            }
            return *this;
        }

        x::physics::force & force::operator=(x::physics::force && o) noexcept
        {
            if(&o != this)
            {
                x::reality::variable<x::real>::operator=(x::move(o));

                __k = o.__k;

                o.__k = 0.01f;
            }
            return *this;
        }

        void force::update()
        {
            if(__current != __value)
            {
                __interval = __interval + 1.0f;
                __current = force::calculate(__current, __initial, __value, __interval, __k);
                x::console::out << __current << x::endl << x::flush;
            }
            else
            {
                __interval = 0.0f;
            }
        }

        void force::value(const x::real & v)
        {
            if(v <= 0)
            {
                __interval = (__current == this->__value ? 0 : __interval/4);

                __initial = __current;
                __current = this->__value;

                this->__value = 0;
            }
            else
            {
                __interval = (__current == this->__value ? 0 : __interval/4);

                __initial = __current;
                __current = this->__value;

                this->__value = v;
            }
        }

        void force::value(x::real && v)
        {
            if(v <= 0)
            {
                v = 0;
            }

            __interval = (__current == this->__value ? 0 : __interval/4);

            __initial = __current;
            __current = this->__value;

            this->__value = v;
        }
    }
}
