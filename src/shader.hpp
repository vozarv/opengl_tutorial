#pragma once

#include "GL/glew.h"
#include "camera.hpp"
#include "transform.hpp"
#include <string>

class Shader {

public:
  Shader(const std::string &fileName);

  void Bind();
  void Update(const Transform &transform, const Camera &camera/*,
              const float &lightIntensity, glm::vec3 lightDirection,
              glm::vec4 color*/);

  virtual ~Shader();

protected:
private:
  enum {
    MODEL_U,
    VIEW_U,

    VIEWPOS_U,
    MATERIAL_SHININESS_U,

    DIRLIGHT_DIRECTION_U,
    DIRLIGHT_AMBIENT_U,
    DIRLIGHT_DIFFUSE_U,
    DIRLIGHT_SPECULAR_U,

    POINTLIGHT_POSITION_U,
    POINTLIGHT_AMBIENT_U,
    POINTLIGHT_DIFFUSE_U,
    POINTLIGHT_SPECULAR_U,
    POINTLIGHT_CONSTANT_U,
    POINTLIGHT_LINEAR_U,
    POINTLIGHT_QUADRATIC_U,

    NUM_UNIFORMS
  };

  static const unsigned int NUM_SHADERS = 2;

  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];
};