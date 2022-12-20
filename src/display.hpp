#pragma once

#include "stdio.h"
#include "string"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>

class Display {
public:
  Display(int width, int height, const std::string &title);

  void Update();
  bool IsClosed();
  void Clear(float r, float g, float b, float a);
  void Close();

  virtual ~Display();

protected:
private:
  SDL_Window *m_window;
  SDL_GLContext m_glContext;
  bool m_is_closed;
};