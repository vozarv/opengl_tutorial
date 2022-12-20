#pragma once

#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "display.hpp"
#include <SDL2/SDL_events.h>
#include <bits/types/time_t.h>
#include <chrono>

class Keyboard {

public:
  Keyboard();
  ~Keyboard();
  void Update(Camera &camera, Display &display);

protected:
private:
  float lastFrame = 0;
  time_t deltaTime = 0;
};