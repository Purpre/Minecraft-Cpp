#include <blocks/blocks.hpp>

Block GRASS_BLOCK("grass_block");
Block GRASS("grass");
Block COBBLESTONE("cobblestone");
Block DIRT("dirt");
Block STONE("stone");
Block OAK_LOG("oak_log");
Block OAK_LEAVES("oak_leaves");

void BlockRegistry::registerBlocks()
{
    glm::vec3 GRASS_colorModifier = glm::vec3(0.666667f, 1.13725f, 0.364706f);

    GRASS_BLOCK.texture.topTexture.texture = glm::vec2(0, 15);
    GRASS_BLOCK.texture.topTexture.colorModifier = GRASS_colorModifier;
    GRASS_BLOCK.texture.sideTexture.texture = glm::vec2(3, 15);
    GRASS_BLOCK.texture.bottomTexture.texture = glm::vec2(2, 15);
    Block::registerBlock(GRASS_BLOCK);

    GRASS.texture.sideTexture.texture = glm::vec2(7, 13);
    GRASS.texture.sideTexture.colorModifier = GRASS_colorModifier;
    GRASS.texture.meshType = CROSS;
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

    OAK_LOG.texture.topTexture.texture = glm::vec2(5, 14);
    OAK_LOG.texture.sideTexture.texture = glm::vec2(4, 14);
    OAK_LOG.texture.bottomTexture.texture = glm::vec2(5, 14);
    Block::registerBlock(OAK_LOG);

    glm::vec3 OAK_LEAVES_colorModifier = glm::vec3(0.4f, 1.0f, 0.25f);

    OAK_LEAVES.texture.topTexture.texture = glm::vec2(5, 12);
    OAK_LEAVES.texture.topTexture.colorModifier = OAK_LEAVES_colorModifier;
    OAK_LEAVES.texture.sideTexture.texture = glm::vec2(5, 12);
    OAK_LEAVES.texture.sideTexture.colorModifier = OAK_LEAVES_colorModifier;
    OAK_LEAVES.texture.bottomTexture.texture = glm::vec2(5, 12);
    OAK_LEAVES.texture.bottomTexture.colorModifier = OAK_LEAVES_colorModifier;
    Block::registerBlock(OAK_LEAVES);
}