#include "standard.hh"
#include "../shaders/standard.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace programs
            {
                namespace standard
                {
                    x::graphics::program program("standard", {
                                                     x::graphics::opengl::shaders::standard::vertex,
                                                     x::graphics::opengl::shaders::standard::fragment
                                                 },
                                                 {"mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength"});
                }
            }
        }
    }
}
