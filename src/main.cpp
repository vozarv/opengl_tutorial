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

void DrawOnScreen(){
    //TODO
}
 

int main(int, char**) {

    Display display(WIDTH, HEIGHT, "Hello Monkey!");

    Shader shader("./res/textureShader");
    Texture texture("./res/bricks.jpg");
    Transform transform;
    Camera camera(glm::vec3(0,0,-5), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;
            
    //Mesh mesh_triangle(triangle, sizeof(triangle)/sizeof(triangle[0]), triangle_indices, sizeof(triangle_indices)/sizeof(triangle_indices[0]));
    Mesh mesh_triangle("./res/triangle.obj");
    Mesh mesh_monkey("./res/monkey3.obj");
    Mesh mesh_tetrahedron("./res/tetrahedron.obj");
    Mesh mesh_cube("./res/cube.obj");

    float r = 0;
    float g = 0.15f;
    float b = 0.1f;
    float lightIntensity = 1.0f;
    int sign = 1;

    while(!display.IsClosed())
    {

        /*
        if(r > 1)
            sign = -1;
        if(r < 0)
            sign = 1;

        r += sign * 0.01f;
        */
        /*
        lightIntensity -= sign * 0.01f;
        if(lightIntensity < 0.2)
            lightIntensity = 0.2;
        */
        lightIntensity = 1.0f;
        //transform.GetPos().x = sinf(counter / 10);
        //transform.GetPos().z = cosf(counter / 10);
        //transform.GetRot().x = counter / 11;
        transform.GetRot().y = -counter / 10;
        //transform.GetRot().z = counter / 23;
        //transform.GetScale() = glm::vec3(1.0,1.0,1.0) * abs(cosf(counter / 23));


        
        display.Clear(r, g, b, 1.0f);
        //TODO Draw funkció inputokkal: shader, texture, transform, mesh
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera, lightIntensity);


        //mesh_monkey.Draw();
        //mesh_tetrahedron.Draw();
        mesh_cube.Draw();
        //mesh_triangle.Draw();


        display.Update();
        counter += 0.1f;
        usleep(10000);
    }

}
