#include <world/chunk.hpp>

void GenerateOakTree(std::unordered_map<glm::vec3, uint8_t, Vec3Hash> &terrain, int x, int z, int groundY)
{
    int trunkHeight = 6;

    for (int y = 0; y < trunkHeight; y++)
    {
        terrain[{x, groundY + y, z}] = OAK_LOG;
    }

    int top = groundY + trunkHeight;

    terrain[{x, top, z}] = OAK_LEAVES;

    for (int y = 0; y > -4; y--)
    {
        if (y == 0)
        {
            for (int i = -1; i <= 1; i += 2)
                terrain[{x + i, top + y, z}] = OAK_LEAVES;
            for (int i = -1; i <= 1; i += 2)
                terrain[{x, top + y, z + i}] = OAK_LEAVES;
        }
        else
        {
            for (int i = -1; i <= 1; i += 2)
                terrain[{x + i, top + y, z}] = OAK_LEAVES;
            for (int i = -1; i <= 1; i += 2)
                terrain[{x + i, top + y, z - 1}] = OAK_LEAVES;
            for (int i = -1; i <= 1; i += 2)
                terrain[{x + i, top + y, z + 1}] = OAK_LEAVES;
            for (int i = -1; i <= 1; i += 2)
                terrain[{x, top + y, z + i}] = OAK_LEAVES;
        }
    }
    for (int _x = 0; _x < 5; _x++)
    {
        for (int y = 0; y < 2; y++)
        {
            terrain[{x - 2, top - 3 + y, z + _x - 2}] = OAK_LEAVES;
            terrain[{x + 2, top - 3 + y, z + _x - 2}] = OAK_LEAVES;
        }
    }
    for (int _x = 0; _x < 3; _x++)
    {
        for (int y = 0; y < 2; y++)
        {
            terrain[{x + _x - 1, top - 3 + y, z + 2}] = OAK_LEAVES;
            terrain[{x + _x - 1, top - 3 + y, z - 2}] = OAK_LEAVES;
        }
    }
}

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

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> distrib(1, 1000);
                int random_num = distrib(gen);

                if (random_num == 1)
                {
                    GenerateOakTree(terrain, x, y, height - 31);
                }
                else if (random_num > 1 && random_num < 10)
                {
                    // terrain.insert({glm::vec3(x, height - 31, y), GRASS});
                }

                terrain.insert({glm::vec3(x, height - 32, y), GRASS_BLOCK});
                terrain.insert({glm::vec3(x, height - 33, y), DIRT});
                terrain.insert({glm::vec3(x, height - 34, y), STONE});
                terrain.insert({glm::vec3(x, height - 35, y), STONE});
            }
        }
    }
}