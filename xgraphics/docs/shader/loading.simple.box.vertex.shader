attribute vec4 vertexPosition;
precision mediump float;
uniform float progress;
varying vec2 vTexCoord;

void main(){
    gl_PointSize = 1.0;
    gl_Position = vertexPosition;

    vTexCoord = vertexPosition.xy;
}
