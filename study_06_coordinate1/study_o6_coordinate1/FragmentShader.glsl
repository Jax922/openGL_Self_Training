#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = texture(ourTexture, ourTexCoord);
    FragColor = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), 0.2);
}

