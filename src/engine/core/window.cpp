#include <engine/core/window.hpp>

using std::cerr;

void Window::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::Window(const char *name, unsigned int sizex, unsigned int sizey)
{
    this->win = glfwCreateWindow(sizex, sizey, name, NULL, NULL);
    if (this->win == NULL)
    {
        cerr << "Failed to create window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cerr << "Failed to init GLAD\n";
        glfwTerminate();
        return;
    }
}

