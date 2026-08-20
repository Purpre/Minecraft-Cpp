#include <iostream>

#include <engine/core/window.hpp>
#include <engine/geometry/mesh.hpp>
#include <engine/core/shader.hpp>
#include <engine/core/texture.hpp>
#include <engine/core/camera.hpp>
#include <blocks/blocks.hpp>
#include <world/chunk.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::cout, std::string, glm::vec3, glm::vec2;

int main()
{
    BlockRegistry::registerBlocks();

    Window::init();

    Window window("Minecraft C++", 1000, 800);

    Camera camera;

    Texture texture("../assets/terrain.png");
    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    camera.setup(shader, window);

    Chunk chunk;
    chunk.pos = vec2(0, 0);
    chunk.generateTerrain();

    chunk.generateMesh();
    chunk.setupMesh(shader);

    double lastTime = glfwGetTime();
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture.bind(); 
        shader.Use();
        chunk.draw();
        camera.update(delta, window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}