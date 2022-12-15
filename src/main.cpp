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
 

int main(int, char**) {

    Display display(WIDTH, HEIGHT, "Hello Monkey!");

    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Transform transform;
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;
                   

    unsigned int indices[] = { 0, 1, 2};
    Mesh mesh_triangle(triangle, sizeof(triangle)/sizeof(triangle[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh mesh_triangle2(triangle_z, sizeof(triangle_z)/sizeof(triangle_z[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh mesh2("./res/monkey3.obj");

    float r = 0;
    float g = 0.15f;
    float b = 0.1f;
    float lightIntensity = 1.0f;
    int sign = 1;

    while(!display.IsClosed())
    {


        if(r > 1)
            sign = -1;
        if(r < 0)
            sign = 1;

        r += sign * 0.01f;
        /*
        lightIntensity -= sign * 0.01f;
        if(lightIntensity < 0.2)
            lightIntensity = 0.2;
        */
        lightIntensity = 1.0f;
        transform.GetPos().x = sinf(counter / 10);
        transform.GetPos().z = cosf(counter / 10);
        transform.GetRot().y = counter / 10;
        //transform.GetScale() = glm::vec3(1.0,1.0,1.0) * abs(cosf(counter / 23));


        
        display.Clear(r, g, b, 1.0f);
        //TODO Draw funkció inputokkal: shader, texture, transform, mesh
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera, lightIntensity);
        mesh2.Draw();
        mesh_triangle.Draw();
        //mesh_triangle2.Draw();

        display.Update();



        counter += 0.1f;
        usleep(10000);
    }

}
