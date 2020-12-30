#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexNormal;
layout(location = 2) in vec4 vertexColor;
layout(location = 3) in vec2 vertexUV;
uniform mat4 mvp;
out vec4 Normal;
out vec4 FragPos;
out vec2 TexturePos;

void main(){
    gl_Position = mvp * vertexPosition;
    FragPos = vertexPosition;
    TexturePos = vertexUV;
    Normal = vertexNormal;
}
