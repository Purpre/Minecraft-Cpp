#pragma once

#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <engine/geometry/mesh.hpp>
#include <world/block.hpp>
#include <engine/core/shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vec3Hash
{
    std::size_t operator()(const glm::vec3 &v) const
    {
        std::size_t h1 = std::hash<float>()(v.x);
        std::size_t h2 = std::hash<float>()(v.y);
        std::size_t h3 = std::hash<float>()(v.z);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class Chunk
{
private:
    Mesh chunkMesh;
    MeshBuilder builder;

public:
    std::unordered_map<glm::vec3, uint8_t, Vec3Hash> terrain;
    glm::vec2 pos;

    void generateMesh();
    void setupMesh(Shader shader);
    void draw();
};