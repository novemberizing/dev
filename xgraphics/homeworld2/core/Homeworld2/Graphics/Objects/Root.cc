#include "Root.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            Root::Root(x::graphics::reference * reference, Homeworld2::Graphics::Objects::Joint * root)
            :   x::graphics::objects::root(root),
                __reference(reference)
            {
            }

            Root::~Root()
            {
                __reference = nullptr;
            }
        }
    }
}
