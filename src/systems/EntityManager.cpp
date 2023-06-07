#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_cameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_cameraComponent;
}

Entity EntityManager::getCurrentWeaponEntity() const { return m_currentWeapon; }

void EntityManager::setCurrentWeaponEntity(Entity newEntity) {
  m_currentWeapon = newEntity;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  return m_renderableEntities;
}

std::vector<Entity> EntityManager::getCollidableEntites() const {
  return m_collidableEntities;
};

Entity EntityManager::getCurrentSkyboxEntity() const { return m_currentSkybox; }

void EntityManager::addRenderableEntity(Entity newRenderableEntity) {
  m_renderableEntities.push_back(newRenderableEntity);
}

void EntityManager::addSkyboxEntity(Entity newSkyboxEntity) {
  m_skyboxEntities.push_back(newSkyboxEntity);
  m_currentSkybox = newSkyboxEntity;
}

void EntityManager::addCollidableEntity(Entity newCollidableEntity) {
  m_collidableEntities.push_back(newCollidableEntity);
}