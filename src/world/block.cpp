#include <world/block.hpp>

using std::string;

uint8_t Block::blockAmmount = 0;

std::unordered_map<uint8_t, Block> Block::blocks = {};

void Block::registerBlock(Block block)
{
    blocks.insert({block.ID, block});
}

Block::Block(string name)
{
    this->ID = blockAmmount;
    blockAmmount++;
    this->name = name;
}

Block Block::getBlockByID(uint8_t ID)
{
    if (blocks.find(ID) != blocks.end())
        return blocks.find(ID)->second;
    else
        return Block("null");
}