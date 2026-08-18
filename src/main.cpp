#include <iostream>

#include <engine/core/window.hpp>
#include <engine/geometry/mesh.hpp>
#include <engine/core/shader.hpp>

using std::cout, std::string;

int main()
{
    Window::init();

    Window window("Minecraft C++", 800, 600);
                        // Position         // UV           // Color              // Normal
    float vertices[] = { 0.5f, 0.5f, 0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
                         0.5f,-0.5f, 0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
                        -0.5f,-0.5f, 0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
                        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f};

    unsigned int indices[] = {0, 1, 3,
                              1, 2, 3};

    Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices));

    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        mesh.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}