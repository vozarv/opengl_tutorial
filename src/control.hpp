#pragma once

#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "player.hpp"
#include "display.hpp"
#include <SDL2/SDL_events.h>
#include <chrono>

class Control {

public:
  Control();
  ~Control();
  void Update(Player &player, Display &display);

protected:
private:
  int lastFrame;
  int deltaTime;
  float m_baseTurningSpeed = 0.01f;
  float m_baseMovementSpeed = 0.1f;
  //bool toggleButton = false;
  //glm::vec2 mousePosition;
};