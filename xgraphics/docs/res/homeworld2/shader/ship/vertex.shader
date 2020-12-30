attribute vec4 vertexPosition;
attribute vec4 vertexNormal;
attribute vec2 vertexUV;
uniform mat4 mvp;
uniform sampler2D textureSampler;
varying vec4 Normal;
varying vec4 FragPos;
varying vec2 texturePos;
void main(){
    gl_Position = mvp * vertexPosition;
    FragPos = vertexPosition;
    Normal = vertexNormal;
    texturePos = vertexUV;
}
