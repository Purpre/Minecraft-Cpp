#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Window
{
public:
    static void init();
    Window(const char *name, unsigned int sizex, unsigned int sizey);
    GLFWwindow *win;

    operator GLFWwindow *() const
    {
        return win;
    }
};