#include "EntityFactory.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/TextureComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp"

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_EntityManager(entityManager), m_ResourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType,
                                             glm::vec3 position,
                                             glm::vec3 rotation,
                                             glm::vec3 scale) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::SHOTGUN:
    model = m_ResourceManager.getModel(EntityType::SHOTGUN);
    shader = m_ResourceManager.getShader(EntityType::SHOTGUN);
    break;
  case EntityType::TERRAIN:
    model = m_ResourceManager.getModel(EntityType::TERRAIN);
    shader = m_ResourceManager.getShader(EntityType::TERRAIN);
    break;
  }

  m_EntityManager.addComponent<ModelComponent>(newEntity,
                                               ModelComponent(model));
  m_EntityManager.addComponent<ShaderComponent>(newEntity,
                                                ShaderComponent(shader));
  m_EntityManager.addComponent<TransformComponent>(
      newEntity, TransformComponent(position, rotation, scale));
  m_EntityManager.addRenderableEntity(newEntity);

  return newEntity;
}

void EntityFactory::createSkyboxEntity() {

  Entity newEntity = getNewEntityId();
  m_EntityManager.addComponent<TextureComponent>(
      newEntity,
      TextureComponent(m_ResourceManager.getTexture(EntityType::SKYBOX)));
  m_EntityManager.addComponent<ShaderComponent>(
      newEntity,
      ShaderComponent(m_ResourceManager.getShader(EntityType::SKYBOX)));
  m_EntityManager.addComponent<SkyboxModelComponent>(
      newEntity, m_ResourceManager.getSkyboxModel());
  m_EntityManager.addSkyboxEntity(newEntity);
};

Entity EntityFactory::createWeaponEntity(EntityType entityType,
                                         glm::vec3 scale) {

  Entity weaponEntity = createRenderableEntity(entityType);
  m_EntityManager.addComponent<WeaponComponent>(weaponEntity,
                                                WeaponComponent());
  m_EntityManager.setCurrentWeaponEntity(weaponEntity);
  return weaponEntity;
}