#include "coordinate.system.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace shaders
            {
                namespace coordinate
                {
                    namespace system
                    {
                        x::graphics::shader vertex("coordinate system vertex",
                                                   x::graphics::shader::vertex,
                                                   "#version 330 core\n"
                                                   "layout(location = 0) in vec4 vertexPosition;\n"
                                                   "layout(location = 1) in vec4 vertexNormal;\n"
                                                   "layout(location = 2) in vec4 vertexColor;\n"
                                                   "uniform mat4 mvp;\n"
                                                   "out vec4 fragmentColor;\n"
                                                   "void main(){\n"
                                                   "    gl_Position = mvp * vertexPosition;\n"
                                                   "    fragmentColor = vertexColor;\n"
                                                   "}");
                        x::graphics::shader fragment("coordinate system fragment",
                                                     x::graphics::shader::fragment,
                                                     "#version 330 core\n"
                                                     "in vec4 fragmentColor;\n"
                                                     "out vec4 color;\n"
                                                     "void main(){\n"
                                                     "    color = fragmentColor;\n"
                                                     "}");
                    }
                }
            }
        }
    }
}
