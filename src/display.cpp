#include "display.hpp"
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include "GLFW/glfw3.h"

Display::Display(int width, int height, const std::string &title)
{

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //TODO Windows-Linux incompatibility
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
  m_glContext = SDL_GL_CreateContext(m_window);

  GLenum status = glewInit();

  if (status != GLEW_OK)
  {
    std::cerr << "Glew failed to initialize!" << std::endl;
  }

  m_is_closed = false;

  glEnable(GL_DEPTH_TEST);

  // Only when using convex models
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);

  // Blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Anti-Aliasing
  glEnable(GL_MULTISAMPLE);

  // Gamma-Correction
  glEnable(GL_FRAMEBUFFER_SRGB); 

  SDL_SetWindowResizable(m_window, SDL_TRUE);

  m_width = width;
  m_height = height;
}

Display::~Display()
{

  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Display::Update()
{
  SDL_GL_SwapWindow(m_window);

  SDL_Event e;

  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
      m_is_closed = true;
  }
}

void Display::Close() { m_is_closed = true; }

bool Display::IsClosed() { return m_is_closed; }

void Display::Clear(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
