#include "Single.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            Single::Single(const x::string & name, Homeworld2::Graphics::Objects::Lod * object)
            :   x::graphics::objects::single(object),
                __name(name)
            {
            }

            Single::~Single()
            {
            }
        }
    }
}
