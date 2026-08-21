#include <blocks/blocks.hpp>

Block GRASS("grass");
Block COBBLESTONE("cobblestone");
Block DIRT("dirt");
Block STONE("stone");

void BlockRegistry::registerBlocks()
{
    GRASS.texture.topTexture.texture = glm::vec2(0, 15);
    GRASS.texture.topTexture.colorModifier = glm::vec3(0.666667f, 1.13725f, 0.364706f);
    GRASS.texture.sideTexture.texture = glm::vec2(3, 15);
    GRASS.texture.bottomTexture.texture = glm::vec2(2, 15);
    Block::registerBlock(GRASS);

    COBBLESTONE.texture.topTexture.texture = glm::vec2(0, 14);
    COBBLESTONE.texture.sideTexture.texture = glm::vec2(0, 14);
    COBBLESTONE.texture.bottomTexture.texture = glm::vec2(0, 14);
    Block::registerBlock(COBBLESTONE);

    DIRT.texture.topTexture.texture = glm::vec2(2, 15);
    DIRT.texture.sideTexture.texture = glm::vec2(2, 15);
    DIRT.texture.bottomTexture.texture = glm::vec2(2, 15);
    Block::registerBlock(DIRT);

    STONE.texture.topTexture.texture = glm::vec2(1, 15);
    STONE.texture.sideTexture.texture = glm::vec2(1, 15);
    STONE.texture.bottomTexture.texture = glm::vec2(1, 15);
    Block::registerBlock(STONE);
}