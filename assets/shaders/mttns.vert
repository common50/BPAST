#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
out vec3 meowtexColor;
out vec2 meowtexCoord;
out vec3 meowMal;
out vec3 fragPaws;
uniform mat4 meowdel;
uniform mat4 miew;
uniform mat4 meowjection;
void main() {
    gl_Position = meowjection * miew * meowdel * vec4(aPos, 1.0);
    fragPaws = vec3(meowdel * vec4(aPos, 1.0));
    meowMal = mat3(transpose(inverse(meowdel))) * aNormal;
    meowtexColor = aColor;
    meowtexCoord = aTexCoord;
}
