#include "coordinate.system.hh"
#include "../shaders/coordinate.system.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace programs
            {
                namespace coordinate
                {
                    namespace system
                    {
                        x::graphics::program program("coordinate system", {
                                                         x::graphics::opengl::shaders::coordinate::system::vertex,
                                                         x::graphics::opengl::shaders::coordinate::system::fragment
                                                     },
                                                     {"mvp"});
                    }
                }
            }
        }
    }
}
