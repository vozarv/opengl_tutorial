#include <GL/glew.h>
#include "display.hpp"
#include <glm/fwd.hpp>
#include <unistd.h>
#include "shader.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "vertex_list.h"

#define WIDTH 800 //TODO getter in display
#define HEIGHT 600 //TODO getter in display

void DrawOnScreen(Camera camera, Mesh &mesh, Shader &shader, Texture &texture, Transform &transform, float lightIntensity, glm::vec3 lightDirection, glm::vec4 color){

    shader.Bind();
    texture.Bind(0);
    shader.Update(transform, camera, lightIntensity, lightDirection, color);
    mesh.Draw();

}

Transform Offset(float x, float y, float z)
{
    Transform transform;
    transform.GetPos().x = x;
    transform.GetPos().y = y;
    transform.GetPos().z = z;
    return transform;
}
 

int main(int, char**) {

    Display display(WIDTH, HEIGHT, "Hello Monkey!");

    Shader shader_tex("./res/textureShader");
    Shader shader_color("./res/colorShader");
    Texture texture_bricks("./res/bricks.jpg"); 
    Texture texture_torch("./res/torch.jpg");
    Texture texture_camouflage("./res/camouflage.jpg");

    Transform transform_rot;
    Camera camera(glm::vec3(0,0,-7), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
    float counter = 0.0f;
            
    //Mesh mesh_triangle(triangle, sizeof(triangle)/sizeof(triangle[0]), triangle_indices, sizeof(triangle_indices)/sizeof(triangle_indices[0]));
    Mesh mesh_triangle("./res/triangle.obj");
    Mesh mesh_monkey("./res/monkey3.obj");
    Mesh mesh_tetrahedron("./res/tetrahedron.obj");
    Mesh mesh_cube("./res/cube.obj");
    Mesh mesh_logo("./res/logo.obj");

    glm::vec4 background_color = glm::vec4(0, 0.15f, 0.1f, 1.0f);
    glm::vec3 lightDirection = glm::vec3(0,0,1);
    glm::vec4 color = glm::vec4(1,0,0,1);
    float lightIntensity = 1.0f;
    int sign = 1;

    while(!display.IsClosed())
    {
        
        transform_rot.GetRot().y = counter / 70;
        transform_rot.GetRot().z = counter / 110;
        lightDirection.x = cosf(counter / 20);
        lightDirection.z = sinf(counter / 20);
        color.b = abs(cosf(counter/ 30));
        color.g = abs(cosf(counter/ 50));

        
        display.Clear(background_color.r, background_color.g, background_color.b, background_color.a);
        
        transform_rot.GetPos().x = -2;
        transform_rot.GetPos().y = -1;
        transform_rot.GetPos().z = 0;
        DrawOnScreen(camera, mesh_tetrahedron, shader_tex, texture_bricks, transform_rot, lightIntensity, lightDirection, color);

        transform_rot.GetPos().x = 1;
        transform_rot.GetPos().y = 2;
        transform_rot.GetPos().z = 3;
        DrawOnScreen(camera, mesh_cube, shader_tex, texture_torch, transform_rot, lightIntensity, lightDirection, color);

        transform_rot.GetPos().x = 3;
        transform_rot.GetPos().y = 0;
        transform_rot.GetPos().z = -1;
        DrawOnScreen(camera, mesh_monkey, shader_tex, texture_camouflage, transform_rot, lightIntensity, lightDirection, color);    

        transform_rot.GetPos().x = 0;
        transform_rot.GetPos().y = 0;
        transform_rot.GetPos().z = 0;
        transform_rot.GetRot().x = counter / 20;
        transform_rot.GetRot().y = 0;
        transform_rot.GetRot().z = 3.14 / 2;

        DrawOnScreen(camera, mesh_logo, shader_tex, texture_camouflage, transform_rot, lightIntensity, lightDirection, color);              
  
        display.Update();

        counter += 0.1f;
        usleep(10000);
    }

}
