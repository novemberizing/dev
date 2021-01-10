#include "object.hh"

namespace x
{
    namespace physics
    {
        // object::object(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up)
        // :   __name(name),
        //     __physics(nullptr),
        //     __force(0),
        //     __position(position),
        //     __front(front),
        //     __up(up)
        // {
        // }
        //
        // object::object(const x::string & name, x::physics::reference * physics, x::real force, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up)
        // :   __name(name),
        //     __physics(physics),
        //     __force(force),
        //     __position(position),
        //     __front(front),
        //     __up(up)
        // {
        // }

        object::object()
        :   x::reality::object()
        {
        }

        object::~object()
        {
        }
    }
}
