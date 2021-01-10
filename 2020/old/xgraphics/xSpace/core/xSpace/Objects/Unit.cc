#include "Unit.hh"

namespace xSpace
{
    namespace Objects
    {
        Unit::Unit(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, x::graphics::object * graphics)
        :   xSpace::Object(name, position, front, up, graphics)
        {
        }

        Unit::~Unit()
        {
        }
    }
}
