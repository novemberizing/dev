#include "Ship.hh"

namespace xSpace
{
    namespace Objects
    {
        namespace Units
        {
            Ship::Ship(const x::string & name, const x::reality::vector & position, const x::reality::vector & front, const x::reality::vector & up, x::graphics::object * graphics)
            :   xSpace::Objects::Unit(name, position, front, up, graphics)
            {
            }

            Ship::~Ship()
            {
            }
        }
    }
}
