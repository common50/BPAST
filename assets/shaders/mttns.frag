#version 330 core
in vec3 meowtexColor;
in vec2 meowtexCoord;
in vec3 meowMal;
in vec3 fragPaws;
out vec4 FragColor;

uniform sampler2D meowtex;
uniform bool huhTexture;
uniform vec3 materialColor;
uniform float meowterialSpec;
uniform float meowterialShiny;
uniform vec3 viewPaws;

#define MAX_LIGHTS 8

struct Light {
    int   type;
    vec3  position;
    vec3  direction;
    vec3  color;
    float intensity;
    float range;
};

uniform Light lights[MAX_LIGHTS];
uniform int   lightCount;
uniform vec3  sceneAmbient;


// i asked a more qualified person to make me the frag and vert shader
// idk what this is all about tbh
void main() {
    vec3 baseColor = (huhTexture ? texture(meowtex, meowtexCoord).rgb : meowtexColor) * materialColor;

    vec3 norm    = normalize(meowMal);
    vec3 viewDir = normalize(viewPaws - fragPaws);

    vec3 result = sceneAmbient;

    for (int i = 0; i < lightCount && i < MAX_LIGHTS; i++) {
        vec3  toLight;
        float atten = 1.0;

        if (lights[i].type == 0) {
            toLight = normalize(-lights[i].direction);
        } else {
            vec3  d    = lights[i].position - fragPaws;
            float dist = length(d);
            toLight    = d / dist;
            float t    = clamp(1.0 - dist / lights[i].range, 0.0, 1.0);
            atten      = t * t;
        }

        vec3  lightCol = lights[i].color * lights[i].intensity * atten;
        float diff     = max(dot(norm, toLight), 0.0);

        float spec = 0.0;
        if (diff > 0.0) {
            vec3 reflectDir = reflect(-toLight, norm);
            spec = pow(max(dot(viewDir, reflectDir), 0.0), max(meowterialShiny, 1.0));
        }

        result += lightCol * (diff + meowterialSpec * spec);
    }

    FragColor = vec4(result * baseColor, 1.0);
}
