#include "standard.hh"

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            namespace shaders
            {
                namespace standard
                {
                    x::graphics::shader vertex("standard vertex",
                                               x::graphics::shader::vertex,
                                               "#version 330 core\n"
                                               "layout(location = 0) in vec4 vertexPosition;\n"
                                               "layout(location = 1) in vec4 vertexNormal;\n"
                                               "layout(location = 2) in vec4 vertexColor;\n"
                                               "layout(location = 3) in vec2 vertexUV;\n"
                                               "uniform mat4 mvp;\n"
                                               "out vec4 Normal;\n"
                                               "out vec4 FragPos;\n"
                                               "out vec2 TexturePos;\n"
                                               "void main(){\n"
                                               "    gl_Position = mvp * vertexPosition;\n"
                                               "    FragPos = vertexPosition;\n"
                                               "    TexturePos = vertexUV;\n"
                                               "    Normal = vertexNormal;\n"
                                               "}");
                    x::graphics::shader fragment("standard fragment",
                                                 x::graphics::shader::fragment,
                                                 "#version 330 core\n"
                                                 "uniform vec4 cameraPos;\n"
                                                 "uniform vec4 lightColor;\n"
                                                 "uniform vec4 lightPos;\n"
                                                 "uniform float ambientStrength;\n"
                                                 "in vec4 Normal;\n"
                                                 "in vec4 FragPos;\n"
                                                 "in vec2 TexturePos;\n"
                                                 "out vec4 color;\n"
                                                 "void main(){\n"
                                                 "    vec4 viewDir = normalize(cameraPos - FragPos);\n"
                                                 "    vec4 norm = normalize(Normal);\n"
                                                 "    vec4 direction = normalize(lightPos - FragPos);\n"
                                                 "    float diff = max(dot(norm, direction), 0.0);\n"
                                                 "    vec4 diffuse = diff * lightColor;\n"
                                                 "    vec4 ambient = ambientStrength * lightColor;\n"
                                                 "    vec4 reflectDir = reflect(-direction, norm);\n"
                                                 "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
                                                 "    vec4 specular = 0.5 * spec * lightColor;\n"
                                                 "    color = vec4(vec3((ambient + diffuse + specular) * lightColor), 1.0);\n"
                                                 "}");
                }
            }
        }
    }
}
