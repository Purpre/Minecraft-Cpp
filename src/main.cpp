#include <iostream>

#include <engine/core/window.hpp>
#include <engine/geometry/mesh.hpp>
#include <engine/core/shader.hpp>
#include <engine/core/texture.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::cout, std::string, glm::vec3, glm::vec2;

int main()
{
    Window::init();

    Window window("Minecraft C++", 800, 800);

    MeshBuilder builder;
    builder.AddFace(FRONT, vec3(0, 0, 0), vec2(0, 15), vec3(0, 0, 1), vec3(0.666667f, 1.13725f, 0.364706f));

    Texture texture("../assets/terrain.png");

    Mesh mesh(builder.vertices.data(), builder.vertices.size() * sizeof(float), builder.indices.data(), builder.indices.size() * sizeof(float));

    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture.bind();
        shader.Use();
        mesh.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}