#include "src/systems/EntityFactory.hpp"
#include "src/systems/EntityManager.hpp"
#include "src/systems/InputSystem.hpp"
#include "src/systems/RenderSystem.hpp"

#include "src/engine/Mesh.hpp"
#include "src/engine/Shader.hpp"

#include "src/components/CameraComponent.hpp"
#include "src/components/GraphicsComponent.hpp"
#include "src/components/TransformComponent.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(1920, 1080, "Game", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cout << "Error!" << std::endl;
  }

  CameraComponent camera(glm::vec3(0.0f, 2.0f, 0.0f));
  EntityManager entity_manager;
  entity_manager.addCameraComponent(camera);
  EntityFactory entity_factory(entity_manager);
  entity_factory.createRenderableEntity("resources/meshes/senti.obj",
                                        "resources/textures/senti.png",
                                        "resources/shaders/basic.shader");
  RenderSystem render_system(entity_manager);

  InputSystem input_system(window, entity_manager);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    float currentFrame = glfwGetTime();
    auto lastFrame = currentFrame;
    float deltaTime = currentFrame - lastFrame;

    // Aktualizacja systemów
    input_system.update(deltaTime);
    render_system.update();

    // Rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Wymiana buforów i obsługa zdarzeń
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}