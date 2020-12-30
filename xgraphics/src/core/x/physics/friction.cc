#include "friction.hh"

namespace x
{
    namespace physics
    {
        x::real friction::calculate(x::real velocity)
        {
            return velocity >= 1 ? velocity * velocity : velocity;
        }
    }
}
