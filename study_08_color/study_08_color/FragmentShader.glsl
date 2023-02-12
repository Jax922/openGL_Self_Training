#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
//in vec2 ourTexCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // FragColor = texture(ourTexture, ourTexCoord);
    // FragColor = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), 0.2);
    FragColor = vec4(lightColor * objectColor, 1.0);
}

