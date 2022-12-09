#version 330 core
out vec4 FragColor;

varying vec2 tmp;

uniform sampler2D diffuse;



void main()
{
    //FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    FragColor = texture2D(diffuse, tmp);
} 