#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0; //TODO add color to varying
varying vec4 color0;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texCoord0 = texCoord;
    normal0 = (transform * vec4(normal.x, normal.y, normal.z, 0.0)).xyz;

    color0 = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);

}