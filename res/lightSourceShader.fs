#version 330 core
out vec4 FragColor;

uniform sampler2D diffuse;
uniform float lightIntensity;
uniform vec3 lightDirection;
uniform vec4 color;


void main()
{
    FragColor = vec4(1.0);
} 