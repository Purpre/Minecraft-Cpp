#include <iostream>

#include <engine/core/window.hpp>
#include <engine/geometry/mesh.hpp>
#include <engine/core/shader.hpp>
#include <engine/core/texture.hpp>
#include <engine/core/camera.hpp>
#include <blocks/blocks.hpp>
#include <world/chunk.hpp>
#include <world/world.hpp>
#include <engine/core/renderer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::cout, std::string, glm::vec3, glm::vec2;

int main()
{
    BlockRegistry::registerBlocks();

    Window::init();

    Window window("Minecraft C++", 1920, 1080);
    Camera camera;
    Texture texture("../assets/terrain.png");
    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    Renderer renderer;
    renderer.window = &window;
    renderer.texture = &texture;
    renderer.shader = &shader;
    renderer.camera = &camera;

    camera.setup(shader, window);

    World world;
    world.generateWorld(24);
    world.setupChunkMeshes(shader);

    double lastTime = glfwGetTime();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        renderer.render(world.chunks, delta);

        glfwSwapBuffers(window);           
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}