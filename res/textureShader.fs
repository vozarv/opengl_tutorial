#version 330 core
out vec4 FragColor;

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
uniform float lightIntensity;



void main()
{
    vec3 lightDirection = vec3(0,0,1) * lightIntensity; // TODO változtatható fény irány
    FragColor = texture2D(diffuse, texCoord0) * clamp(max(dot(-lightDirection, normal0),dot(lightDirection, normal0)), 0.0, 1.0);
} 