#version 330 core

in vec2 TexCoord;
in vec3 Color;
in vec3 Normal;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    float intensity = 1.0;

    if (Normal.x < 0.0 || Normal.y < 0.0 || Normal.x > 0.0)
        intensity = 0.7;

    if (Normal.z < 0.0 || Normal.z > 0.0)
        intensity = 0.8;

    vec4 texColor = texture(ourTexture, TexCoord);
    FragColor = texColor * vec4(Color * intensity, 1.0);
}