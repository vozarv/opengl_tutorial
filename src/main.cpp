
#include <GL/glew.h>
#include "display.hpp"
#include <unistd.h>
#include "shader.hpp"


int main(int, char**) {

    Display display(800, 600, "Hello World!");

    Shader shader("./res/basicShader");

    float r = 0;
    int sign = 1;

    while(!display.IsClosed())
    {


        if(r > 1)
            sign = -1;
        if(r < 0)
            sign = 1;

        r += sign * 0.01f;


        display.Clear(r, 0.15f, 0.3f, 1.0f);
        display.Update();
        usleep(10000);
    }

}


