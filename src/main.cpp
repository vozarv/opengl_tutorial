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

  Shader shader("./res/shaders/dummy.vs", "./res/shaders/dummy.fs");
  Shader shader_background("./res/shaders/backgroundShader.vs", "./res/shaders/backgroundShader.fs");
  Shader shader_complex("./res/shaders/complexShader.vs", "./res/shaders/complexShader.fs", "./res/shaders/geometryShader.gs");

  Model backpack("./res/objects/backpack/backpack.obj");
  //Model MLU("./res/objects/MLU.obj");

  Model cube("./res/objects/cube.obj");

  Transform transform;
  //transform.SetScale(glm::vec3(0.2, 0.2, 0.2));
  // transform.SetRot(glm::vec3(-PI / 2, PI, 0.0));
  // transform.SetPos(glm::vec3(-25.0, 20.0, 0.0));

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

    // view/projection transformations
    shader.setMat4("projection", player.m_camera.GetProjection());
    shader.setMat4("view", player.m_camera.GetView());

    // render the loaded model
    glm::mat4 model = transform.GetModel();

    shader.setMat4("model", model);

    // MLU.Draw(shader);
    backpack.Draw(shader_complex);
    //cube.Draw(shader);

    display.Update();

    counter += 0.1f;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //auto tmp = player.m_camera.GetForward();
    // std::cout << tmp.x << " " << tmp.y << std::endl;
  }

  return 0;
}
