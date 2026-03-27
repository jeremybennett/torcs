#version 330 core
layout(location=0) out vec4 fragColor;
layout(location=1) out vec4 brightColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;
in vec2 fragTexCoord2;
in vec4 fragPosLightSpace;

uniform sampler2D texture1;
uniform sampler2D shadowMap;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 viewPos;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

float shadowCalculation(vec4 fragPosLS) {
    vec3 projCoords = fragPosLS.xyz / fragPosLS.w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z > 1.0) return 0.0;
    float currentDepth = projCoords.z;
    float bias = 0.005;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;
}

void main() {
    vec4 texColor = texture(texture1, fragTexCoord);
    if (texColor.a < 0.1) discard;

    vec3 norm = normalize(fragNormal);
    vec3 lDir = normalize(lightDir);

    // Ambient
    vec3 ambient = ambientColor * matAmbient.rgb * texColor.rgb;

    // Diffuse
    float diff   = max(dot(norm, lDir), 0.0);
    vec3 diffuse = diff * lightColor * matDiffuse.rgb * texColor.rgb;

    // Specular (Blinn-Phong)
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfDir = normalize(lDir + viewDir);
    float shininess = matShininess > 0.0 ? matShininess : 32.0;
    float spec   = pow(max(dot(norm, halfDir), 0.0), shininess);
    vec3 specular = spec * lightColor * matSpecular.rgb;

    // Shadow
    float shadow = shadowCalculation(fragPosLightSpace);

    vec3 result = ambient + (1.0 - shadow) * (diffuse + specular);
    fragColor = vec4(result, texColor.a);

    // Bright pass for bloom
    float luminance = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if (luminance > 1.0)
        brightColor = vec4(result, 1.0);
    else
        brightColor = vec4(0.0, 0.0, 0.0, 1.0);
}
