#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct blockFaceTexture
{
    glm::vec2 texture;
    glm::vec3 colorModifier = glm::vec3(1.0f, 1.0f, 1.0f);
};

struct BlockTexture
{
    blockFaceTexture topTexture;
    blockFaceTexture sideTexture;
    blockFaceTexture bottomTexture;
};

class Block
{
public:
    static uint8_t blockAmmount;
    static void registerBlock(Block block);
    static std::unordered_map<uint8_t, Block> blocks;

    static Block getBlockByID(uint8_t ID);

    Block(std::string name);

    uint8_t ID;
    BlockTexture texture;

    std::string name;
};