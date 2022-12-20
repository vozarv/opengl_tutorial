#include "keyboard.hpp"
#include <SDL2/SDL_keyboard.h>
#include <iostream>

Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

void Keyboard::Update(Camera &camera) {

  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

  if (currentKeyStates[SDL_SCANCODE_W]) {
    camera.RotateTilt(0.01);
  }
  if (currentKeyStates[SDL_SCANCODE_S]) {
    camera.RotateTilt(-0.01);
  }
  if (currentKeyStates[SDL_SCANCODE_A]) {
    camera.RotatePan(0.01);
  }
  if (currentKeyStates[SDL_SCANCODE_D]) {
    camera.RotatePan(-0.01);
  }
  if (currentKeyStates[SDL_SCANCODE_Q]) {
    camera.RotateRoll(-0.01);
  }
  if (currentKeyStates[SDL_SCANCODE_UP]) {
    camera.Move(camera.GetForward() / 10.0f);
  }
  if (currentKeyStates[SDL_SCANCODE_DOWN]) {
    camera.Move(camera.GetForward() / -10.0f);
  }
}