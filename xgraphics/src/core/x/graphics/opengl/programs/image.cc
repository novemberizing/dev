#include "simple.hh"
#include "../shaders/image.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace programs
            {
                namespace image
                {
                    x::graphics::program program("image", {
                                                     x::graphics::opengl::shaders::image::vertex,
                                                     x::graphics::opengl::shaders::image::fragment
                                                 },
                                                 {"mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength", "textureSampler"});
                }
            }
        }
    }
}
