#pragma once

#include "camera.hpp"
#include <SDL2/SDL_events.h>

class Keyboard {

public:
  Keyboard();
  ~Keyboard();
  void Update(Camera &camera);

protected:
private:
};