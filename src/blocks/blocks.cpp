#include <blocks/blocks.hpp>

void BlockRegistry::registerBlocks()
{
    Block GRASS("grass");
    GRASS.texture.topTexture.texture = glm::vec2(0, 15);
    GRASS.texture.topTexture.colorModifier = glm::vec3(0.666667f, 1.13725f, 0.364706f);
    GRASS.texture.sideTexture.texture = glm::vec2(3, 15);
    GRASS.texture.bottomTexture.texture = glm::vec2(2, 15);
    Block::registerBlock(GRASS);

    Block COBBLESTONE("cobblestone");
    COBBLESTONE.texture.topTexture.texture = glm::vec2(0, 14);
    COBBLESTONE.texture.sideTexture.texture = glm::vec2(0, 14);
    COBBLESTONE.texture.bottomTexture.texture = glm::vec2(0, 14);
    Block::registerBlock(COBBLESTONE);
}