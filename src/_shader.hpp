#pragma once

#include "GL/glew.h"
#include "camera.hpp"
#include "player.hpp"
#include "transform.hpp"
#include <string>

class Shader {

public:
  Shader(const std::string &fileName);
  Shader(const std::string &fileName, const std::string &geometryFileName);

  void Bind();
  void Update(const Transform &transform, const Player &player,
              glm::vec3 lightPos); // TODO player, lights class
  void Update(const Player &player);
  void UpdateBackground(const Transform &transform, const Player &player,
                        glm::vec3 lightPos);
  virtual ~Shader();
  
  GLuint m_program;

protected:
private:
  void updateUniform(const std::string &uniformName, float value);
  void updateUniform(const std::string &uniformName, int value);
  void updateUniform(const std::string &uniformName, glm::vec3 value);
  void updateUniform(const std::string &uniformName, glm::mat4 value);

  static const unsigned int NUM_SHADERS = 3;

  GLuint m_shaders[NUM_SHADERS];
};