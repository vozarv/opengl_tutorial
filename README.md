## Making .obj files
o <name>

v <vec3>  #list all vertex coordinates

vt <vec2> #list all texture coordinates

s off

f <num_of_vertex>/<num_of_tex_coord> ... #list all polygons built from vertexes 


o Tetrahedron

v   1.000000  0.000000 -0.707107

v  -1.000000  0.000000 -0.707107

v   0.000000 -1.000000  0.707107 

v   0.000000  1.000000. 0.707107

vt -0.500000 -0.500000

vt  0.000000  0.500000

vt  0.500000 -0.500000

usemtl None

s off

f 1/1 2/2 3/3

f 1/1 2/2 4/3

f 1/1 3/2 4/3

f 2/1 3/2 4/3



## CMRC install
https://github.com/vector-of-bool/cmrc