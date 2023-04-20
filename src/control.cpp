#include "control.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <chrono>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include <SDL2/SDL_mouse.h>

// TODO add mouse input

Control::Control() {

  lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
                  (std::chrono::system_clock::now()).time_since_epoch())
                  .count();

  deltaTime = 0;

  SDL_SetRelativeMouseMode(SDL_TRUE);
}

Control::~Control() {}

void Control::Update(Camera &camera, Display &display) {

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
    camera.Move(m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetForward()));
  }
  if (currentKeyStates[SDL_SCANCODE_S]) {
    camera.Move(-1 * m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetForward()));
  }
  if (currentKeyStates[SDL_SCANCODE_A]) {
    camera.Move(m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetLeft()));
  }
  if (currentKeyStates[SDL_SCANCODE_D]) {
    camera.Move(m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetRight()));
  }
  if (currentKeyStates[SDL_SCANCODE_Q]) {
    camera.RotateRoll(-1 * m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_E]) {
    camera.RotateRoll(m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_SPACE]) {
    camera.Move(m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetUp()));
  }
  if (currentKeyStates[SDL_SCANCODE_LSHIFT]) {
    camera.Move(-1 * m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetUp()));
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

  camera.RotatePan(-x / 3 * m_baseTurningSpeed * sensitivity);
  camera.RotateTilt(-y / 3 * m_baseTurningSpeed * sensitivity);

  // std::cout << x << " " << y << std::endl;
  // display.centerMouse();
}