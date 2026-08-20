#include <world/world.hpp>

void World::generateWorld(int radius)
{
    for (int y = -radius; y < radius; y++)
    {
        for (int x = -radius; x < radius; x++)
        {
            Chunk chunk;
            chunk.pos = glm::vec2(x, y);
            chunk.generateTerrain();
            chunk.generateMesh();
            chunks.push_back(chunk);
        }
    }
}

void World::setupChunkMeshes(Shader shader)
{
    for (Chunk &chunk : chunks)
    {
        chunk.setupMesh(shader);
    }
}