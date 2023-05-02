#include "control.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <chrono>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include <SDL2/SDL_mouse.h>


Control::Control() {

  lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
                  (std::chrono::system_clock::now()).time_since_epoch())
                  .count();

  deltaTime = 0;

  SDL_SetRelativeMouseMode(SDL_TRUE);
}

Control::~Control() {}

void Control::Update(Player &player, Display &display) {

  auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                         (std::chrono::system_clock::now()).time_since_epoch())
                         .count();

  deltaTime = currentTime - lastFrame;
  lastFrame = currentTime;

  float sensitivity = glm::clamp(deltaTime / 20.0f, 0.01f, 100.0f);

  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

  if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
    display.Close();
  }
  if (currentKeyStates[SDL_SCANCODE_W]) {
    player.m_camera.Move(m_baseMovementSpeed * sensitivity *
                         glm::normalize(player.m_camera.GetHorizontalForward()));
  }
  if (currentKeyStates[SDL_SCANCODE_S]) {
    player.m_camera.Move(-1 * m_baseMovementSpeed * sensitivity *
                         glm::normalize(player.m_camera.GetHorizontalForward()));
  }
  if (currentKeyStates[SDL_SCANCODE_A]) {
    player.m_camera.Move(m_baseMovementSpeed * sensitivity *
                         glm::normalize(player.m_camera.GetLeft()));
  }
  if (currentKeyStates[SDL_SCANCODE_D]) {
    player.m_camera.Move(m_baseMovementSpeed * sensitivity *
                         glm::normalize(player.m_camera.GetRight()));
  }
  if (currentKeyStates[SDL_SCANCODE_Q]) {
    player.m_camera.RotateRoll(-1 * m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_E]) {
    player.m_camera.RotateRoll(m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_SPACE]) {
    player.m_camera.Move(m_baseMovementSpeed * sensitivity *
                         glm::normalize(player.m_camera.GetUp()));
  }
  if (currentKeyStates[SDL_SCANCODE_LSHIFT]) {
    player.m_camera.Move(-1 * m_baseMovementSpeed * sensitivity *
                         glm::normalize(player.m_camera.GetUp()));
  }
  if (currentKeyStates[SDL_SCANCODE_R]) {
    player.setLight();
  }
  if (currentKeyStates[SDL_SCANCODE_T]) {
    player.resetLight();
  }

  int w = display.getWidth() / 2;
  int h = display.getHeight() / 2;
  int x = 0;
  int y = 0;

  // SDL_GetMouseState(&x, &y);

  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_MOUSEMOTION) {
    x = event.motion.xrel;
    y = event.motion.yrel;
  }

  /*
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
    toggleButton = true;
    if (player.getSwitch()) {
      player.setLight();
    } else
      player.resetLight();
    std::cout << player.getSwitch() << std::endl;
  }*/

  //  if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r) {
  //    toggleButton = false;
  //  }

  player.m_camera.RotatePan(-x / 3 * m_baseTurningSpeed * sensitivity);
  player.m_camera.RotateTilt(-y / 3 * m_baseTurningSpeed * sensitivity);

  // std::cout << x << " " << y << std::endl;
  // display.centerMouse();
}