#pragma once

#include <vector>

#include <world/chunk.hpp>
#include <engine/core/shader.hpp>

class World
{
public:
    void generateWorld(int radius);
    void setupChunkMeshes(Shader shader);

    std::vector<Chunk> chunks;
};