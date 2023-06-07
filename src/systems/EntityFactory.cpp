#include "EntityFactory.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/TextureComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp"
#include <random>

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_entityManager(entityManager), m_resourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_nextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType,
                                             glm::vec3 position,
                                             glm::vec3 rotation,
                                             glm::vec3 scale) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::SHOTGUN:
    model = m_resourceManager.getModel(EntityType::SHOTGUN);
    shader = m_resourceManager.getShader(EntityType::SHOTGUN);
    break;
  case EntityType::TERRAIN:
    model = m_resourceManager.getModel(EntityType::TERRAIN);
    shader = m_resourceManager.getShader(EntityType::TERRAIN);
    break;
  case EntityType::FLOATING_ROCK:
    model = m_resourceManager.getModel(EntityType::FLOATING_ROCK);
    shader = m_resourceManager.getShader(EntityType::FLOATING_ROCK);
    break;
  }

  m_entityManager.addComponent<ModelComponent>(newEntity,
                                               ModelComponent(model));
  m_entityManager.addComponent<ShaderComponent>(newEntity,
                                                ShaderComponent(shader));
  m_entityManager.addComponent<TransformComponent>(
      newEntity, TransformComponent(position, rotation, scale));
  m_entityManager.addRenderableEntity(newEntity);

  return newEntity;
}

void EntityFactory::createSkyboxEntity() {

  Entity newEntity = getNewEntityId();
  m_entityManager.addComponent<TextureComponent>(
      newEntity,
      TextureComponent(m_resourceManager.getTexture(EntityType::SKYBOX)));
  m_entityManager.addComponent<ShaderComponent>(
      newEntity,
      ShaderComponent(m_resourceManager.getShader(EntityType::SKYBOX)));
  m_entityManager.addComponent<SkyboxModelComponent>(
      newEntity, m_resourceManager.getSkyboxModel());
  m_entityManager.addSkyboxEntity(newEntity);
};

Entity EntityFactory::createWeaponEntity(EntityType entityType,
                                         glm::vec3 scale) {

  Entity weaponEntity = createRenderableEntity(entityType);
  m_entityManager.addComponent<WeaponComponent>(weaponEntity,
                                                WeaponComponent());
  m_entityManager.setCurrentWeaponEntity(weaponEntity);
  return weaponEntity;
}

void EntityFactory::createRandomRenderableEntities(EntityType entityType,
                                                   unsigned int amount) {
  for (int i = 0; i < amount; i++) {
    float randomPositionX = generateRandomFloat(-2000.0f, 2000.0f);
    float randomPositionY = generateRandomFloat(
        m_entityManager.getCameraComponent().getPosition().y + 200.0f, 2000.0f);
    float randomPositionZ = generateRandomFloat(-2000.0f, 2000.0f);
    float scale = generateRandomFloat(150.0f, 200.0f);
    float randomRotationX = generateRandomFloat(-180.0f, 180.0f);
    float randomRotationY = generateRandomFloat(-180.0f, 180.0f);
    float randomRotationZ = generateRandomFloat(-180.0f, 180.0f);
    createRenderableEntity(
        entityType,
        glm::vec3(randomPositionX, randomPositionY, randomPositionZ),
        glm::vec3(randomRotationX, randomRotationY, randomRotationZ),
        glm::vec3(scale));
  }
}

float EntityFactory::generateRandomFloat(float lower, float upper) {
  static std::random_device rd;
  static std::mt19937 engine(rd());
  std::uniform_real_distribution<float> dist(lower, upper);
  return dist(engine);
}