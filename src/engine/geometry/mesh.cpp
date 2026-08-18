#include <engine/geometry/mesh.hpp>

using std::vector, glm::vec3, glm::vec2;

vector<float> FrontVertices = {0.5f, 0.5f, 0.5f,
                               0.5f, -0.5f, 0.5f,
                               -0.5f, -0.5f, 0.5f,
                               -0.5f, 0.5f, 0.5f};
vector<float> BackVertices = {0.5f, 0.5f, -0.5f,
                              0.5f, -0.5f, -0.5f,
                              -0.5f, -0.5f, -0.5f,
                              -0.5f, 0.5f, -0.5f};
vector<float> TopVertices = {0.5f, 0.5f, 0.5f,
                             -0.5f, 0.5f, 0.5f,
                             -0.5f, 0.5f, -0.5f,
                             0.5f, 0.5f, -0.5f};
vector<float> BottomVertices = {0.5f, -0.5f, 0.5f,
                                -0.5f, -0.5f, 0.5f,
                                -0.5f, -0.5f, -0.5f,
                                0.5f, -0.5f, -0.5f};
vector<float> RightVertices = {0.5f, 0.5f, 0.5f,
                               0.5f, -0.5f, 0.5f,
                               0.5f, -0.5f, -0.5f,
                               0.5f, 0.5f, -0.5f};
vector<float> LeftVertices = {-0.5f, 0.5f, 0.5f,
                              -0.5f, -0.5f, 0.5f,
                              -0.5f, -0.5f, -0.5f,
                              -0.5f, 0.5f, -0.5f};

std::unordered_map<side, vector<float>> faceVertices = {
    {FRONT, FrontVertices},
    {BACK, BackVertices},
    {TOP, TopVertices},
    {BOTTOM, BottomVertices},
    {RIGHT, RightVertices},
    {LEFT, LeftVertices}};

std::unordered_map<side, glm::vec3> faceNormals = {
    {FRONT, vec3(0.0f, 0.0f, 1.0f)},
    {BACK, vec3(0.0f, 0.0f, -1.0f)},
    {TOP, vec3(0.0f, 1.0f, 0.0f)},
    {BOTTOM, vec3(0.0f, -1.0f, 0.0f)},
    {RIGHT, vec3(1.0f, 0.0f, 0.0f)},
    {LEFT, vec3(-1.0f, 0.0f, 0.0f)}};

Mesh::Mesh(float vertices[],
           size_t vertexSize,
           unsigned int indices[],
           size_t indexSize)
{
    this->indexCount = indexSize / sizeof(unsigned int);

    // Generate VAO, VBO, and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO, VBO, and EBO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture UV
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Color modifier
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void MeshBuilder::AddFace(side faceSide,
                          vec3 pos,
                          vec2 atlasTile,
                          vec3 normal,
                          vec3 color)
{
    int tileX = atlasTile.x; // Columm
    int tileY = atlasTile.y; // Line

    float texSize = 1.0f / 16.0f;

    float u = tileX * texSize;
    float v = tileY * texSize;

    vector<float> VerticesBuffer = faceVertices[faceSide];

    vec3 faceNormal = faceNormals[faceSide];

    vertices.insert(vertices.end(), {pos.x + VerticesBuffer[0], pos.y + VerticesBuffer[1], pos.z + VerticesBuffer[2], u + texSize, v + texSize, color.x, color.y, color.z, faceNormal.x, faceNormal.y, faceNormal.z,
                                     pos.x + VerticesBuffer[3], pos.y + VerticesBuffer[4], pos.z + VerticesBuffer[5], u + texSize, v, color.x, color.y, color.z, faceNormal.x, faceNormal.y, faceNormal.z,
                                     pos.x + VerticesBuffer[6], pos.y + VerticesBuffer[7], pos.z + VerticesBuffer[8], u, v, color.x, color.y, color.z, faceNormal.x, faceNormal.y, faceNormal.z,
                                     pos.x + VerticesBuffer[9], pos.y + VerticesBuffer[10], pos.z + VerticesBuffer[11], u, v + texSize, color.x, color.y, color.z, faceNormal.x, faceNormal.y, faceNormal.z});
    unsigned int offset = vertices.size() / 11 - 4;

    indices.insert(indices.end(), {offset + 0,
                                   offset + 1,
                                   offset + 3,
                                   offset + 1,
                                   offset + 2,
                                   offset + 3});
}