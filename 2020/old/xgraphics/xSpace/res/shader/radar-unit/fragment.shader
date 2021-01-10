#version 330 core

uniform sampler2D textureSampler;
uniform vec4 _color;
in vec2 TexturePos;
out vec4 color;

void main(){
    color = _color;
}
