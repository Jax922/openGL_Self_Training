#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexCoords;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, ourTexCoords) * vec4(ourColor, 1.0f);
}

