#version 330 core
layout(location = 0) in vec4 __position;
layout(location = 1) in vec4 __normal;
layout(location = 2) in vec4 __color;
layout(location = 3) in vec2 __texture;

uniform mat4 _matrix;

out vec4 Normal;
out vec4 FragPos;
out vec2 TexturePos;

void main(){
    gl_Position = _matrix * __position;

    FragPos = __position;
    TexturePos = __texture;
    Normal = __normal;
}
