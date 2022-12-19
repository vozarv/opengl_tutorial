#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/ext/matrix_clip_space.hpp>

class Camera {
public:
  Camera(const glm::vec3 &pos, float fov, float aspect, float zNear,
         float zFar) {
    m_perspective = glm::perspective(fov, aspect, zNear, zFar);
    m_position = pos;
    m_forward = glm::vec3(0, 0, -1); // TODO write getter
    m_up = glm::vec3(0, 1, 0);       // TODO write getter
  }

  inline glm::mat4 GetViewProjection() const {
    return m_perspective *
           glm::lookAt(m_position, m_position + m_forward, m_up);
  }
  inline glm::vec3 GetPosition() const { return m_position; }
  inline glm::vec3 GetForward() const { return m_forward; }
  inline glm::vec3 GetUp() const { return m_up; }

  inline void SetPosition(const glm::vec3 position) { m_position = position; }
  inline void SetForward(const glm::vec3 forward) { m_forward = forward; }
  inline void SetUp(const glm::vec3 up) { m_up = up; }

protected:
private:
  glm::mat4 m_perspective;
  glm::vec3 m_position;
  glm::vec3 m_forward;
  glm::vec3 m_up;
};