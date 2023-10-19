#include "camera.hpp"
#include "display.hpp"
#include "model.h"

#include "background.hpp"
#include "control.hpp"
#include "player.hpp"

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

  Display display(WIDTH, HEIGHT, "Awesome World");
  Control control;
  Background background("./res/textures/city/");

  Shader shader("./res/shaders/materialShader.vs",
                "./res/shaders/materialShader.fs");
  Shader shader_t("./res/shaders/textureShader.vs",
                  "./res/shaders/textureShader.fs");
  Shader shader_background("./res/shaders/backgroundShader.vs",
                           "./res/shaders/backgroundShader.fs");

  Model backpack("./res/objects/backpack/backpack.obj");
  Model MLU("./res/objects/MLU_simple.obj");

  Model cube("./res/objects/cube.obj");

  Transform transform;
  Transform transform_MLU;
  transform_MLU.SetScale(glm::vec3(0.02, 0.02, 0.02));
  //  transform.SetRot(glm::vec3(-PI / 2, PI, 0.0));
  transform_MLU.SetPos(glm::vec3(-25.0, 0.0, -25.0));

  Player player(glm::vec3(0, 0, 7), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f,
                1000.0f);

  float counter = 0.0f;

  glm::vec4 background_color = glm::vec4(0, 0.25f, 0.2f, 0.5f);
  glm::vec3 lightPos = glm::vec3(3, 0, 0);

  while (!display.IsClosed()) {

    control.Update(player, display);
    display.Clear(background_color.r, background_color.g, background_color.b,
                  background_color.a);

    // Draw Background
    background.Draw(shader_background, player);

    shader.use();
    shader.setMat4("projection", player.m_camera.GetProjection());
    shader.setMat4("view", player.m_camera.GetView());
    shader.setMat4("model", transform_MLU.GetModel());
    shader.setVec3("viewPos", player.m_camera.GetPosition());
    shader.setInt("skybox", (int)0);
    shader.setVec3("dirLight.direction", glm::vec3(0.0, -100.0, 0.0));
    shader.setVec3("dirLight.ambient", glm::vec3(0.1, 0.1, 0.1));
    shader.setVec3("dirLight.diffuse", glm::vec3(0.5, 0.5, 0.5));
    shader.setVec3("dirLight.specular", glm::vec3(0.9, 0.9, 0.9));
    MLU.Draw(shader);
    // cube.Draw(shader);

    shader_t.use();
    shader_t.setMat4("projection", player.m_camera.GetProjection());
    shader_t.setMat4("view", player.m_camera.GetView());
    shader_t.setMat4("model", transform_MLU.GetModel());
    shader_t.setVec3("viewPos", player.m_camera.GetPosition());
    shader_t.setInt("skybox", (int)0);
    shader_t.setVec3("dirLight.direction", glm::vec3(0.0, -100.0, 0.0));
    shader_t.setVec3("dirLight.ambient", glm::vec3(0.1, 0.1, 0.1));
    shader_t.setVec3("dirLight.diffuse", glm::vec3(0.5, 0.5, 0.5));
    shader_t.setVec3("dirLight.specular", glm::vec3(0.9, 0.9, 0.9));
    shader_t.setMat4("model", transform.GetModel());
    backpack.Draw(shader_t);


    display.Update();
    counter += 0.1f;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
