#include "Lod.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            Lod::Lod(x::uint32 level)
            :   x::graphics::objects::multi(),
                __level(level)
            {
            }

            Lod::~Lod()
            {
            }

            void Lod::render(const x::reality::vector & position, const x::reality::vector & center)
            {
                // TODO: CALCULATE LEVEL USING CENTER
                if(__level == 0)
                {
                    x::graphics::objects::multi::render(position, center);
                }
            }
        }
    }
}
