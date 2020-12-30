#include "Base.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            Base::Base(x::graphics::reference * reference, x::graphics::program * program, x::graphics::texture * texture)
            :   x::graphics::objects::base(reference, program, texture)
            {
            }

            Base::~Base()
            {
            }
        }
    }
}
