#version 330 core
uniform vec4 cameraPos;
uniform vec4 lightColor;
uniform vec4 lightPos;
uniform float ambientStrength;
uniform sampler2D textureSampler;
in vec4 Normal;
in vec4 FragPos;
in vec2 TexturePos;
out vec4 color;
void main(){
    vec4 viewDir = normalize(cameraPos - FragPos);
    vec4 norm = normalize(Normal);
    vec4 direction = normalize(lightPos - FragPos);
    float diff = max(dot(norm, direction), 0.0);
    vec4 diffuse = diff * lightColor;
    vec4 ambient = ambientStrength * lightColor;
    vec4 reflectDir = reflect(-direction, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = 0.5 * spec * lightColor;
    // color = vec4(vec3((ambient + diffuse + specular) * lightColor), 1.0);
    color = vec4(texture(textureSampler, TexturePos).rgb, 1.0);
}
