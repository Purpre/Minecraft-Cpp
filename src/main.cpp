#include <iostream>

#include <engine/core/window.hpp>

using std::cout, std::string;

int main()
{
    Window::init();

    Window window("Minecraft C++", 800, 600);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}