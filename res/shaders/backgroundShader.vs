#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 model; // Identity matrix, TODO deprecated
uniform mat4 view;

void main() {

  TexCoords = aPos;
  vec4 pos = view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
  gl_Position = pos;
  //gl_Position = pos.xyww;
}