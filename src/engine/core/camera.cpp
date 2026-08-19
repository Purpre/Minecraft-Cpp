#include <engine/core/camera.hpp>

void Camera::mouse_callback(GLFWwindow *window,
                            double xpos,
                            double ypos)
{
    Camera *camera =
        static_cast<Camera *>(glfwGetWindowUserPointer(window));

    camera->MouseMove(xpos, ypos);
}

void Camera::MouseMove(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void Camera::update(float delta, GLFWwindow *win)
{
    const float cameraSpeed = 5.0f * delta; // velocidade normal

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;

    static bool escPressed = false;

    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        if (!escPressed)
        {
            lockMouse = !lockMouse;
            if (!lockMouse)
                glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
                glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            escPressed = true;
        }
    }
    else if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
    {
        escPressed = false;
    }

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::setup(Shader &shader, GLFWwindow *win)
{
    viewLoc = glGetUniformLocation(shader.ShaderProgram, "view");
    projLoc = glGetUniformLocation(shader.ShaderProgram, "projection");

    glfwSetWindowUserPointer(win, this);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(win, mouse_callback);
}