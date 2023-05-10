#include "camera.hpp"
#include "display.hpp"
#include "mesh.hpp"

#include "background.hpp"
#include "control.hpp"
#include "player.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <chrono>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/transform.hpp>
#include <thread>

#define WIDTH 800  // TODO getter in display
#define HEIGHT 600 // TODO getter in display
#define WIREFRAME_MODE false
#define PI 3.14159265359

int main(int, char **) {

  Display display(WIDTH, HEIGHT, "Hello PPE!");
  Control control;
  Background background;

  Shader shader_light_source("./res/shaders/lightSourceShader");
  Shader shader_complex("./res/shaders/complexShader");
  Shader shader_background("./res/shaders/backgroundShader");

  Texture texture_bricks("./res/textures/bricks.jpg");

  Texture texture_grass("./res/textures/grass.png");
  Texture texture_window("./res/textures/blending_transparent_window.png");
  Texture texture_torch("./res/textures/torch.jpg");
  Texture texture_blank("./res/textures/grey.png");
  Texture texture_camouflage("./res/textures/camouflage.jpg");
  Texture texture_container("./res/textures/container2.png");
  Texture texture_container_specular("./res/textures/container2_specular.png");

  Transform transform_logo;
  transform_logo.SetScale(glm::vec3(2, 2.5, 2));

  Transform transform_cube;
  Transform transform_sphere;
  Transform transform_big_cube;
  transform_big_cube.SetScale(glm::vec3(10, 10, 10));
  transform_big_cube.SetPos(glm::vec3(30, 0, 0));
  transform_sphere.SetScale(glm::vec3(2, 2, 2));
  // transform_cube.SetScale(glm::vec3(2, 2, 2));
  //  transform_cube.SetRot(glm::vec3(0, 0.5, 0));
  transform_cube.SetPos(glm::vec3(3, -2, 0));

  Transform transform_light_source;
  transform_light_source.SetPos(glm::vec3(5.0f, 0.0f, 0.0f));
  transform_light_source.SetScale(glm::vec3(0.1, 0.1, 0.1));

  Player player(glm::vec3(0, 0, 7), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f,
                1000.0f);
  float counter = 0.0f;

  Mesh mesh_square("./res/objects/square.obj");
  Mesh mesh_triangle("./res/objects/triangle.obj");
  Mesh mesh_monkey("./res/objects/monkey3.obj");
  Mesh mesh_tetrahedron("./res/objects/tetrahedron.obj");
  Mesh mesh_cube("./res/objects/cube.obj");
  Mesh mesh_logo("./res/objects/logo.obj");
  Mesh mesh_sphere("./res/objects/sphere.obj");

  glm::vec4 background_color = glm::vec4(0, 0.25f, 0.2f, 0.5f);
  glm::vec3 lightPos = glm::vec3(3, 0, 0);
  // glm::vec4 color = glm::vec4(1, 1, 1, 1);
  // float lightIntensity = 1.0f;

  while (!display.IsClosed()) {

    //
    control.Update(player, display);
    lightPos = glm::vec3(3.0 * cosf(counter / 20), 0, 3.0 * sinf(counter / 20));
    display.Clear(background_color.r, background_color.g, background_color.b,
                  background_color.a);



    // Draw Background
    glDepthMask(GL_FALSE);
    shader_background.Bind();
    shader_background.Update(player);
    mesh_cube.Draw(WIREFRAME_MODE);
    glDepthMask(GL_TRUE);



    // Draw light source
    shader_light_source.Bind();
    texture_blank.Bind(0);
    transform_light_source.SetPos(lightPos);
    shader_light_source.Update(transform_light_source, player, lightPos);
    mesh_sphere.Draw(WIREFRAME_MODE);


    // Draw center object
    shader_complex.Bind();
    texture_bricks.Bind(0);
    //texture_container.Bind(0);
    // texture_container_specular.Bind(0);
    shader_complex.Update(transform_sphere, player, lightPos);
    mesh_sphere.Draw(WIREFRAME_MODE);


    // Draw blending object
    texture_window.Bind(0);
    shader_complex.Update(transform_cube, player, lightPos);
    mesh_cube.Draw(WIREFRAME_MODE);


    // Draw big object
    //shader_background.Bind();
    //texture_blank.Bind(0);
    texture_container.Bind(0);
    shader_complex.Update(transform_big_cube, player, lightPos);
    mesh_cube.Draw(WIREFRAME_MODE);

    // background.Draw(shader_background, player);

    display.Update();

    counter += 0.1f;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
