#include "simple.hh"
#include "../shaders/simple.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace programs
            {
                namespace simple
                {
                    x::graphics::program program("simple", {
                                                     x::graphics::opengl::shaders::simple::vertex,
                                                     x::graphics::opengl::shaders::simple::fragment
                                                 });
                }
            }
        }
    }
}
