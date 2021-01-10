#include "Front.hh"

namespace Pioneer
{
    namespace Display
    {
        Front::Front(const x::string & name)
        :   x::graphics::layer(name)
        {
        }

        Front::~Front()
        {
        }
    }
}
