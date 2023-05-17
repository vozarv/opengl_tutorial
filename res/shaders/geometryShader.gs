#version 330 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT {

  vec2 TexCoord;
  vec3 Normal;
  vec3 FragPos;
}
gs_in[];

out GS_OUT {

  vec2 TexCoord;
  vec3 Normal;
  vec3 FragPos;
}
gs_out;

void main() {

  gs_out.Normal = gs_in[0].Normal;
  gs_out.FragPos = gs_in[0].FragPos;
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  gs_out.Normal = gs_in[1].Normal;
  gs_out.FragPos = gs_in[1].FragPos;
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();

  gs_out.Normal = gs_in[2].Normal;
  gs_out.FragPos = gs_in[2].FragPos;
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();

/*
  gl_Position =
      (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3;
  EmitVertex();

  gl_Position =
      (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3 +
      vec4(gs_in[2].Normal, 1.0);
  EmitVertex();
*/
  EndPrimitive();
}