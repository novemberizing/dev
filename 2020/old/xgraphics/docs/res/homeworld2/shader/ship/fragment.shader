precision mediump float;
uniform vec4 cameraPos;
uniform vec4 lightColor;
uniform vec4 lightPos;
uniform float ambientStrength;
uniform sampler2D textureSampler;
varying vec4 Normal;
varying vec4 FragPos;
varying vec2 texturePos;
void main(){
    vec4 viewDir = normalize(cameraPos - FragPos);
    vec4 norm = normalize(Normal);
    vec4 direction = normalize(lightPos - FragPos);
    float diff = max(dot(norm, direction), 0.0);
    vec4 diffuse = diff * lightColor;
    vec4 ambient = ambientStrength * lightColor;
    vec4 reflectDir = reflect(-direction, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec4 specular = 0.5 * spec * lightColor;
    gl_FragColor = vec4(vec3((ambient + diffuse + specular) * lightColor), 1.0);
    gl_FragColor = vec4(texture2D(textureSampler, texturePos).rgb, 1.0);
}
