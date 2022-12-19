#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <string>

class Texture {
public:
  Texture(const std::string &fileName);

  void Bind(unsigned int unit);

  ~Texture();

protected:
private:
  GLuint m_texture;
};