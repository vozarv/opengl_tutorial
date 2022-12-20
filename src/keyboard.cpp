#include "keyboard.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <chrono>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

// TODO rename this class to Control and add mouse input

Keyboard::Keyboard() {

  lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
                  (std::chrono::system_clock::now()).time_since_epoch())
                  .count();

  deltaTime = 0;
}

Keyboard::~Keyboard() {}

void Keyboard::Update(Camera &camera, Display &display) {

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
    camera.RotateTilt(m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_S]) {
    camera.RotateTilt(-1 * m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_A]) {
    camera.RotatePan(m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_D]) {
    camera.RotatePan(-1 * m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_Q]) {
    camera.RotateRoll(-1 * m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_E]) {
    camera.RotateRoll(m_baseTurningSpeed * sensitivity);
  }
  if (currentKeyStates[SDL_SCANCODE_UP]) {
    camera.Move(m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetForward()));
  }
  if (currentKeyStates[SDL_SCANCODE_DOWN]) {
    camera.Move(-1 * m_baseMovementSpeed * sensitivity *
                glm::normalize(camera.GetForward()));
  }
}