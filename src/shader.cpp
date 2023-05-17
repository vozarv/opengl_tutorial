#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <vector>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string &errorMessage);
static std::string LoadShader(const std::string &fileName);
static GLuint CreateShader(const std::string &text, GLenum shaderType);

void Shader::updateUniform(const std::string &uniformName, float value)
{
  glUniform1f(glGetUniformLocation(m_program, uniformName.c_str()), value);
}

void Shader::updateUniform(const std::string &uniformName, int value)
{
  glUniform1i(glGetUniformLocation(m_program, uniformName.c_str()), value);
}

void Shader::updateUniform(const std::string &uniformName, glm::vec3 value)
{
  glUniform3f(glGetUniformLocation(m_program, uniformName.c_str()), value.x,
              value.y, value.z);
}

void Shader::updateUniform(const std::string &uniformName, glm::mat4 value)
{
  glUniformMatrix4fv(glGetUniformLocation(m_program, uniformName.c_str()), 1,
                     GL_FALSE, &value[0][0]);
}

Shader::Shader(const std::string &fileName)
{
  m_program = glCreateProgram();

  m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

  glAttachShader(m_program, m_shaders[0]);
  glAttachShader(m_program, m_shaders[1]);

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true,
                   "Error: Program linking failed: ");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true,
                   "Error: Program is invalid: ");
}

Shader::Shader(const std::string &fileName, const std::string &geometryFileName)
{
  m_program = glCreateProgram();

  m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = CreateShader(LoadShader(geometryFileName + ".gs"), GL_GEOMETRY_SHADER);
  m_shaders[2] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

  glAttachShader(m_program, m_shaders[0]);
  glAttachShader(m_program, m_shaders[1]);
  glAttachShader(m_program, m_shaders[2]);

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true,
                   "Error: Program linking failed: ");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true,
                   "Error: Program is invalid: ");
}

Shader::~Shader()
{
  for (unsigned int i = 0; i < NUM_SHADERS; i++)
  {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
}

void Shader::Bind() { glUseProgram(m_program); }

void Shader::Update(const Transform &transform, const Player &player, glm::vec3 lightPos)
{

  glm::mat4 model = transform.GetModel();
  glm::mat4 view = player.m_camera.GetView();
  glm::mat4 projection = player.m_camera.GetProjection();

  updateUniform("model", model);
  updateUniform("view", view);
  updateUniform("projection", projection);
  updateUniform("viewPos", player.m_camera.GetPosition());

  updateUniform("material.shininess", 32.0f);
  updateUniform("material.diffuse", (int)0);
  updateUniform("material.specular", (int)1);
  updateUniform("dirLight.direction", glm::vec3(0, -10, 0));
  updateUniform("dirLight.ambient", glm::vec3(0.1, 0.1, 0.1));
  updateUniform("dirLight.diffuse", glm::vec3(0.5, 0.5, 0.5));
  updateUniform("dirLight.specular", glm::vec3(0.9, 0.9, 0.9));

  updateUniform("pointLights[0].position", lightPos);
  updateUniform("pointLights[0].ambient", glm::vec3(0, 0, 0));
  updateUniform("pointLights[0].diffuse", glm::vec3(0.0, 0.0, 0.6));
  updateUniform("pointLights[0].specular", glm::vec3(0, 0, 1));
  updateUniform("pointLights[0].constant", 1.0f);
  updateUniform("pointLights[0].linear", 0.09f);
  updateUniform("pointLights[0].quadratic", 0.032f);

  updateUniform("spotLight.state", player.getSwitch());
  updateUniform("spotLight.direction", player.m_camera.GetForward());
  updateUniform("spotLight.cutOff", glm::cos(glm::radians(15.0f)));
  updateUniform("spotLight.outerCutOff", glm::cos(glm::radians(25.0f)));
  updateUniform("spotLight.position", player.m_camera.GetPosition());
  updateUniform("spotLight.constant", 1.0f);
  updateUniform("spotLight.linear", 0.09f);     // 0.09f
  updateUniform("spotLight.quadratic", 0.032f); // 0.032f
  updateUniform("spotLight.ambient", glm::vec3(0.0, 0.0, 0.0));
  updateUniform("spotLight.diffuse", glm::vec3(1.0, 1.0, 1.0));
  updateUniform("spotLight.specular", glm::vec3(1.0, 1.0, 1.0));

  updateUniform("skybox", (int)2);
}

// Used for background
void Shader::Update(const Player &player)
{

  glm::mat4 model = glm::mat4(1.0);
  glm::mat4 view = player.m_camera.GetDirectionalView();
  glm::mat4 projection = player.m_camera.GetProjection();

  updateUniform("model", model);
  updateUniform("view", view);
  updateUniform("projection", projection);
  updateUniform("viewPos", player.m_camera.GetPosition());
}

static GLuint CreateShader(const std::string &text, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);

  if (shader == 0)
  {
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

static std::string LoadShader(const std::string &fileName)
{
  std::ifstream file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if (file.is_open())
  {
    while (file.good())
    {
      getline(file, line);
      output.append(line + "\n");
    }
  }
  else
  {
    std::cerr << "Unable to load shader: " << fileName << std::endl;
  }

  return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string &errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = {0};

  if (isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if (success == GL_FALSE)
  {
    if (isProgram)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);

    std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  }
}
