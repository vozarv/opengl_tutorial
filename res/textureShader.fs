#version 330 core
out vec4 FragColor;

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
uniform float lightIntensity;
uniform vec3 lightDirection;
uniform vec4 color;  //TODO deprecated


void main()
{
    vec3 light = lightDirection * lightIntensity;
    FragColor = texture2D(diffuse, texCoord0) * clamp(max(dot(-light, normal0),dot(light, normal0)), 0.0, 1.0);
} 