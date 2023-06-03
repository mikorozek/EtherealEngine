#include "TransformComponent.hpp"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

glm::mat4 TransformComponent::createTransformMatrix() const {
  glm::mat4 transform = glm::mat4(1.0f);

  transform = glm::translate(transform, m_Position);
  transform = glm::rotate(transform, glm::radians(m_Rotation.x),
                          glm::vec3(1.0f, 0.0f, 0.0f));
  transform = glm::rotate(transform, glm::radians(m_Rotation.y),
                          glm::vec3(0.0f, 1.0f, 0.0f));
  transform = glm::rotate(transform, glm::radians(m_Rotation.z),
                          glm::vec3(0.0f, 0.0f, 1.0f));
  transform = glm::scale(transform, m_Scale);

  return transform;
}