#pragma once

#include "GL/glew.h"
#include "camera.hpp"
#include "transform.hpp"
#include <string>

class Shader {

public:
  Shader(const std::string &fileName);

  void Bind();
  void Update(const Transform &transform, const Camera &camera,
              const float &lightIntensity, glm::vec3 lightDirection,
              glm::vec4 color);

  virtual ~Shader();

protected:
private:
  enum {
    TRANSFORM_U,
    LIGHT_INTENSITY_U,
    LIGHT_DIRECTION_U,
    COLOR_U,

    NUM_UNIFORMS
  };

  static const unsigned int NUM_SHADERS = 2;

  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];
};