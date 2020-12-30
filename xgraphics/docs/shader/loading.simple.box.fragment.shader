precision mediump float;
uniform float progress;
varying vec2 vTexCoord;

void main() {
    if(vTexCoord.x < progress)
    {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        // gl_FragColor = vec4(gl_PointCoord, 0.0, 1.0);
    }
    else
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        // gl_FragColor = vec4(gl_PointCoord, 0.0, 1.0);
    }
}
