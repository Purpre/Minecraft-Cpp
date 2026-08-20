#include <world/chunk.hpp>

void Chunk::generateMesh()
{

    std::unordered_set<glm::vec3, Vec3Hash> positions = {glm::vec3(0, 0, 0)};
    positions.clear();

    for (const auto &pair : terrain)
        positions.insert(pair.first);

    for (const auto &pair : terrain)
    {
        glm::vec3 pos = pair.first;
        Block block = Block::getBlockByID(pair.second);

        blockFaceTexture sideTexture = block.texture.sideTexture;
        blockFaceTexture topTexture = block.texture.topTexture;
        blockFaceTexture bottomTexture = block.texture.bottomTexture;

        if (positions.find(pos + glm::vec3(1, 0, 0)) == positions.end())
            builder.AddFace(RIGHT, pos, sideTexture.texture, sideTexture.colorModifier);
        if (positions.find(pos + glm::vec3(-1, 0, 0)) == positions.end())
            builder.AddFace(LEFT, pos, sideTexture.texture, sideTexture.colorModifier);
        if (positions.find(pos + glm::vec3(0, 1, 0)) == positions.end())
            builder.AddFace(TOP, pos, topTexture.texture, topTexture.colorModifier);
        if (positions.find(pos + glm::vec3(0, -1, 0)) == positions.end())
            builder.AddFace(BOTTOM, pos, bottomTexture.texture, bottomTexture.colorModifier);
        if (positions.find(pos + glm::vec3(0, 0, 1)) == positions.end())
            builder.AddFace(FRONT, pos, sideTexture.texture, sideTexture.colorModifier);
        if (positions.find(pos + glm::vec3(0, 0, -1)) == positions.end())
            builder.AddFace(BACK, pos, sideTexture.texture, sideTexture.colorModifier);
    }
}

void Chunk::setupMesh(Shader shader)
{
    this->chunkMesh = Mesh(builder.vertices.data(), builder.vertices.size() * sizeof(float), builder.indices.data(), builder.indices.size() * sizeof(unsigned int));
    this->chunkMesh.SetupModelUniform(shader.ShaderProgram);
}

void Chunk::draw()
{
    this->chunkMesh.Draw();
}

void Chunk::generateTerrain(bool random)
{
    if (!random)
    {
        for (int x = (pos.x * 16) - 8; x < (pos.x * 16) + 8; x++)
        {
            for (int z = (pos.y * 16) - 8; z < (pos.y * 16) + 8; z++)
            {
                terrain.insert({glm::vec3(x, 0, z), 0}); // Grass
                for (int y = -8; y < 0; y++)
                {
                    terrain.insert({glm::vec3(x, y, z), 1}); // Cobblestone
                }
            }
        }
    }
    else
    {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

        for (int y = (pos.x * 16) - 8; y < (pos.x * 16) + 8; y++)
        {
            for (int x = (pos.y * 16) - 8; x < (pos.y * 16) + 8; x++)
            {
                float noiseValue = noise.GetNoise((float)x, (float)y);

                int height = static_cast<int>(
                    (noiseValue + 1.0f) / 2.0f * 64.0f);
                terrain.insert({glm::vec3(x, height - 32, y), 0}); // Grass
            }
        }
    }
}