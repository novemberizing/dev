#include "Multi.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            Multi::Multi(const x::string & name)
            :   x::graphics::objects::multi(),
                __name(name)
            {
            }

            Multi::~Multi()
            {
            }
        }
    }
}
