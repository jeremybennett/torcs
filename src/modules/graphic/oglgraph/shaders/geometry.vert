#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec2 aTexCoord2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;
out vec2 fragTexCoord2;
out vec4 fragPosLightSpace;

void main() {
    vec4 worldPos = model * vec4(aPos, 1.0);
    fragPos       = worldPos.xyz;
    fragNormal    = mat3(transpose(inverse(model))) * aNormal;
    fragTexCoord  = aTexCoord;
    fragTexCoord2 = aTexCoord2;
    fragPosLightSpace = lightSpaceMatrix * worldPos;
    gl_Position = projection * view * worldPos;
}
