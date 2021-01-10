#include "simple.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace shaders
            {
                namespace simple
                {
                    x::graphics::shader vertex("simple vertex",
                                               x::graphics::shader::vertex,
                                               "#version 330 core\n"
                                               "layout(location = 0) in vec4 vertexPosition;\n"
                                               "void main(){\n"
                                               "    gl_Position = vertexPosition;\n"
                                               "}");
                    x::graphics::shader fragment("simple fragment",
                                                 x::graphics::shader::fragment,
                                                 "#version 330 core\n"
                                                 "out vec4 color;\n"
                                                 "void main(){\n"
                                                 "    color = vec4(1.0, 1.0, 1.0, 1.0);\n"
                                                 "}");
                }
            }
        }
    }
}
