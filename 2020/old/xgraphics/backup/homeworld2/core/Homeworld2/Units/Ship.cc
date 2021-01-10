#include "Ship.hh"

namespace Homeworld2
{
    namespace Units
    {
        Ship::Ship(const x::string & name, const x::reality::vector & position, x::real energy, Graphics::Object * graphics)
        :   x::reality::object(name, position),
            Homeworld2::Unit(energy, graphics)
        {
        }

        Ship::Ship(const x::string & name, const x::reality::vector & position, x::real energy, const x::reality::vector & direction, Graphics::Object * graphics)
        :   x::reality::object(name, position),
            Homeworld2::Unit(energy, direction, graphics)
        {
        }

        Ship::Ship(const x::string & name, x::real energy, Graphics::Object * graphics)
        :   x::reality::object(name),
            Homeworld2::Unit(name, energy, graphics)
        {
        }

        Ship::~Ship()
        {
        }
    }
}
