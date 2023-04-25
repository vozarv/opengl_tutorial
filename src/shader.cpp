#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <vector>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string &errorMessage);
static std::string LoadShader(const std::string &fileName);
static GLuint CreateShader(const std::string &text, GLenum shaderType);

Shader::Shader(const std::string &fileName) {
  m_program = glCreateProgram();

  m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glAttachShader(m_program, m_shaders[i]);
  }

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true,
                   "Error: Program linking failed: ");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true,
                   "Error: Program is invalid: ");



m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "view");

m_uniforms[VIEWPOS_U] = glGetUniformLocation(m_program, "viewPos");
m_uniforms[MATERIAL_SHININESS_U] = glGetUniformLocation(m_program, "material.shininess");

m_uniforms[DIRLIGHT_DIRECTION_U] = glGetUniformLocation(m_program, "dirLight.direction");
m_uniforms[DIRLIGHT_AMBIENT_U] = glGetUniformLocation(m_program, "dirLight.ambient");
m_uniforms[DIRLIGHT_DIFFUSE_U] = glGetUniformLocation(m_program, "dirLight.diffuse");
m_uniforms[DIRLIGHT_SPECULAR_U] = glGetUniformLocation(m_program, "dirLight.specular");

m_uniforms[POINTLIGHT_POSITION_U] = glGetUniformLocation(m_program, "pointLights[0].position");
m_uniforms[POINTLIGHT_AMBIENT_U] = glGetUniformLocation(m_program, "pointLights[0].ambient");
m_uniforms[POINTLIGHT_DIFFUSE_U] = glGetUniformLocation(m_program, "pointLights[0].diffuse");
m_uniforms[POINTLIGHT_SPECULAR_U] = glGetUniformLocation(m_program, "pointLights[0].specular");
m_uniforms[POINTLIGHT_CONSTANT_U] = glGetUniformLocation(m_program, "pointLights[0].constant");
m_uniforms[POINTLIGHT_LINEAR_U] = glGetUniformLocation(m_program, "pointLights[0].linear");
m_uniforms[POINTLIGHT_QUADRATIC_U] = glGetUniformLocation(m_program, "pointLights[0].quadratic");


}

Shader::~Shader() {
  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
}

void Shader::Bind() { glUseProgram(m_program); }

void Shader::Update(const Transform &transform, const Camera &camera/*,
                    const float &lightIntensity, glm::vec3 lightDirection,
                    glm::vec4 color*/) {



  glm::mat4 model = transform.GetModel();
  glm::mat4 view = camera.GetViewProjection();

  glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);
  
  glUniform3f(m_uniforms[VIEWPOS_U], camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
  glUniform1f(m_uniforms[MATERIAL_SHININESS_U], 32.0f);
  
  //glUniform3f(m_uniforms[DIRLIGHT_DIRECTION_U], -5.0f, -1.0f, -1.0f);
  //glUniform3f(m_uniforms[DIRLIGHT_AMBIENT_U], 0.05f, 0.05f, 0.05f);
  //glUniform3f(m_uniforms[DIRLIGHT_DIFFUSE_U], 0.4f, 0.4f, 0.4f);
  //glUniform3f(m_uniforms[DIRLIGHT_SPECULAR_U], 0.5f, 0.5f, 0.5f);

  glUniform3f(m_uniforms[POINTLIGHT_POSITION_U], -5.0f, 0.0f, 0.0f);
  glUniform3f(m_uniforms[POINTLIGHT_AMBIENT_U], 0.05f, 0.05f, 0.05f);
  glUniform3f(m_uniforms[POINTLIGHT_DIFFUSE_U], 0.8f, 0.8f, 0.8f);
  glUniform3f(m_uniforms[POINTLIGHT_SPECULAR_U], 1.0f, 1.0f, 1.0f);
  glUniform1f(m_uniforms[POINTLIGHT_CONSTANT_U], 1.0f);
  glUniform1f(m_uniforms[POINTLIGHT_LINEAR_U], 0.09f);
  glUniform1f(m_uniforms[POINTLIGHT_QUADRATIC_U], 0.032f);

}

static GLuint CreateShader(const std::string &text, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);

  if (shader == 0) {
    std::cerr << "Error: Shader creation failed" << std::endl;
  }

  const GLchar *shaderSourceStrings[1];
  GLint shaderSourceStringLengths[1];
  shaderSourceStrings[0] = text.c_str();
  shaderSourceStringLengths[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);

  CheckShaderError(shader, GL_COMPILE_STATUS, false,
                   "Error: Shader compilation failed: ");

  return shader;
}

static std::string LoadShader(const std::string &fileName) {
  std::ifstream file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if (file.is_open()) {
    while (file.good()) {
      getline(file, line);
      output.append(line + "\n");
    }
  } else {
    std::cerr << "Unable to load shader: " << fileName << std::endl;
  }

  return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string &errorMessage) {
  GLint success = 0;
  GLchar error[1024] = {0};

  if (isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if (success == GL_FALSE) {
    if (isProgram)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);

    std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  }
}
