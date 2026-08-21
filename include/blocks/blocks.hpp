#pragma once
#include <world/block.hpp>
#include <unordered_set>

class BlockRegistry
{
public:
    static void registerBlocks();
};

extern Block GRASS;
extern Block COBBLESTONE;
extern Block DIRT;
extern Block STONE;