#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine/core/shader.hpp>

class Camera
{
public:
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void MouseMove(double xpos, double ypos);
    void update(float delta, GLFWwindow *win);
    void setup(Shader &shader, GLFWwindow *win);

private:
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

    unsigned int viewLoc; // glGetUniformLocation(shader.ShaderProgram, "view");
    unsigned int projLoc; // glGetUniformLocation(shader.ShaderProgram, "projection");

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;
    bool lockMouse = true;
};