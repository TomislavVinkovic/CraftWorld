#include "ChunkBlockLayer.h"
#include "Chunk/Chunk.h"

ChunkBlockLayer::ChunkBlockLayer(std::vector<ChunkBlock> blocks, int yLevel)
: blocks(std::move(blocks)) {
    this->yLevel = yLevel;
}

ChunkBlock ChunkBlockLayer::getBlockTypeAt(int x, int z) {
    // it will always be in bounds because i am checking them in the main chunk class
    int index = x*Chunk::chunkSize + z;
    return blocks[index];
}

ChunkBlock ChunkBlockLayer::getBlockAt(int x, int z) {
    // i copied the code instead of reusing the upper function because it is more efficient
    int index = x*Chunk::chunkSize + z;
    if(index > blocks.size()) {
        return ChunkBlock(ChunkBlockType::Air);
    }
    return blocks[index].getType();
}
