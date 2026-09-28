#version 330 core
in vec3 meowtexColor;
in vec2 meowtexCoord;
in vec3 meowMal;
in vec3 fragPaws;
out vec4 FragColor;
uniform sampler2D meowtex;
uniform bool huhTexture;
uniform vec3 lightPaws;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 viewPaws;
uniform float meownCutOff;
uniform float meowterCutOff;
uniform bool crashLightOn;

void main() {
    vec3 baseColor = huhTexture ? texture(meowtex, meowtexCoord).rgb : meowtexColor;

    vec3 ambient = 0.05 * lightCol;

    vec3 norm = normalize(meowMal);
    vec3 toLight = normalize(lightPaws - fragPaws);

    float theta = dot(toLight, normalize(-lightDir));
    float epsilon = meownCutOff - meowterCutOff;
    float spotlight = crashLightOn ? clamp((theta - meowterCutOff) / epsilon, 0.0, 1.0) : 0.0;

    float diff = max(dot(norm, toLight), 0.0);
    vec3 diffuse = diff * lightCol * spotlight;

    vec3 viewDir = normalize(viewPaws - fragPaws);
    vec3 reflectDir = reflect(-toLight, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = 0.5 * spec * lightCol * spotlight;

    FragColor = vec4((ambient + diffuse + specular) * baseColor, 1.0);
}
