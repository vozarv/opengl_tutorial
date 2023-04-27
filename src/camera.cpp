#include "camera.hpp"

Camera::Camera(const glm::vec3 &pos, float fov, float aspect, float zNear,
               float zFar) {
  m_perspective = glm::perspective(fov, aspect, zNear, zFar);
  m_position = pos;
  m_forward = glm::vec3(0, 0, -1);
  m_up = glm::vec3(0, 1, 0);
}

void Camera::Move(const glm::vec3 delta_pos) { 
  m_position += delta_pos;
  m_up = glm::vec3(0, 1, 0); 
  }

void Camera::RotatePan(float angle) {

  glm::mat4 t = glm::rotate(glm::mat4(1), angle, m_up);
  m_forward = glm::vec3(t * glm::vec4(m_forward, 1.0));
}

void Camera::RotateTilt(float angle) {
  glm::mat4 t = glm::rotate(glm::mat4(1), angle, glm::cross(m_forward, m_up));
  m_forward = glm::vec3(t * glm::vec4(m_forward, 1.0));
  m_up = glm::vec3(t * glm::vec4(m_up, 1.0));
}

void Camera::RotateRoll(float angle) {
  glm::mat4 t = glm::rotate(glm::mat4(1), angle, m_forward);
  m_up = glm::vec3(t * glm::vec4(m_up, 1.0));
}
