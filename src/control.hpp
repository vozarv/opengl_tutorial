#pragma once

#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "display.hpp"
#include <SDL2/SDL_events.h>
#include <bits/types/time_t.h>
#include <chrono>

class Control {

public:
  Control();
  ~Control();
  void Update(Camera &camera, Display &display);

protected:
private:
  int lastFrame;
  int deltaTime;
  float m_baseTurningSpeed = 0.01f;
  float m_baseMovementSpeed = 0.1f;
  //glm::vec2 mousePosition;
};