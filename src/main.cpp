#include "camera.hpp"
#include "display.hpp"
#include "mesh.hpp"

#include "keyboard.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "vertex_list.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/transform.hpp>
#include <unistd.h>

#define WIDTH 800  // TODO getter in display
#define HEIGHT 600 // TODO getter in display
#define WIREFRAME_MODE false
#define PI 3.14159265359

void DrawOnScreen(Camera camera, Mesh &mesh, Shader &shader, Texture &texture,
                  Transform &transform, float lightIntensity,
                  glm::vec3 lightDirection, glm::vec4 color) {

  shader.Bind();
  texture.Bind(0);
  shader.Update(transform, camera, lightIntensity, lightDirection, color);
  mesh.Draw(WIREFRAME_MODE);
}

int main(int, char **) {

  Display display(WIDTH, HEIGHT, "Hello PPE!");
  Keyboard keyboard;

  Shader shader_tex("./res/textureShader");
  Shader shader_color("./res/colorShader");
  Texture texture_bricks("./res/bricks.jpg");
  Texture texture_torch("./res/torch.jpg");
  Texture texture_camouflage("./res/camouflage.jpg");

  Transform transform_logo;
  transform_logo.SetScale(glm::vec3(2, 2.5, 2));
  Camera camera(glm::vec3(0, 0, 7), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f,
                1000.0f);
  float counter = 0.0f;

  // Mesh mesh_triangle(triangle, sizeof(triangle)/sizeof(triangle[0]),
  // triangle_indices, sizeof(triangle_indices)/sizeof(triangle_indices[0]));
  Mesh mesh_triangle("./res/triangle.obj");
  Mesh mesh_monkey("./res/monkey3.obj");
  Mesh mesh_tetrahedron("./res/tetrahedron.obj");
  Mesh mesh_cube("./res/cube.obj");
  Mesh mesh_logo("./res/logo.obj");

  glm::vec4 background_color = glm::vec4(0, 0.15f, 0.1f, 1.0f);
  glm::vec3 lightDirection = glm::vec3(0, 0, 1);
  glm::vec4 color = glm::vec4(1, 0, 0, 1);
  float lightIntensity = 1.0f;

  Transform transform[10];
  for (int i = 0; i < 10; i++) {
    transform[i].SetScale(glm::vec3(0.5, 0.5, 0.5));
    transform[i].SetPos(
        glm::vec3(10 * cosf(2 * PI * i / 10), 10 * sinf(2 * PI * i / 10), -3));
  }

  while (!display.IsClosed()) {

    keyboard.Update(camera, display);
    // lightDirection = glm::vec3(cosf(counter / 20), sinf(counter / 20), 0);
    // color = glm::vec4(0, 1, abs(cosf(counter / 30)), 1);

    display.Clear(background_color.r, background_color.g, background_color.b,
                  background_color.a);

    transform_logo.SetRot(glm::vec3(counter / 20 + PI, 0, PI / 2));

    for (int i = 0; i < 10; i++) {
      transform[i].SetRot(glm::vec3(counter / 20 + PI, 0, PI / 2));
      DrawOnScreen(camera, mesh_cube, shader_color, texture_torch, transform[i],
                   lightIntensity, lightDirection, color);
    }

    DrawOnScreen(camera, mesh_logo, shader_tex, texture_torch, transform_logo,
                 lightIntensity, lightDirection, color);

    display.Update();

    counter += 0.1f;
    usleep(1000);
  }
}
