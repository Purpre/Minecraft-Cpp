#pragma once

#include <cmath>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

enum side
{
    TOP,
    BOTTOM,
    RIGHT,
    LEFT,
    FRONT,
    BACK
};

class Mesh
{
public:
    Mesh(float vertices[],
         size_t vertexSize,
         unsigned int indices[],
         size_t indexSize);
    Mesh();

    void Draw();

private:
    GLsizei indexCount;
    unsigned int VAO, VBO, EBO;
};

class MeshBuilder
{
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void AddFace(side faceSide,
                 glm::vec3 pos,
                 glm::vec2 atlasTile,
                 glm::vec3 normal,
                 glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};