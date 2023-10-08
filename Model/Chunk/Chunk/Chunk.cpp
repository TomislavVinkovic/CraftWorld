#include "Chunk.h"
#include "Chunk/ChunkBlockLayer/SingleBlockChunkBlockLayer.h"

Chunk::Chunk(std::vector<std::shared_ptr<IChunkBlockLayer>>& layers, glm::vec3 position) {
    this->blockLayers = std::move(layers);
    this->position = position;

}

ChunkBlock Chunk::getBlockAtPosition(const glm::vec3 &blockPosition) const {
    bool containedInX = blockPosition.x >= position.x && blockPosition.x < position.x + chunkSize;
    bool containedInY = blockPosition.y >= position.y && blockPosition.y < position.y + chunkSize;
    bool containedInZ = blockPosition.z >= position.z && blockPosition.z < position.z + chunkSize;


    // default behavior: return air block
    if(
            !containedInX || !containedInY || !containedInZ
            ) {
        return ChunkBlock(ChunkBlockType::Air);
    }

    int relX = static_cast<int>(floor(blockPosition.x)) & (static_cast<int>(chunkSize)-1);
    int relY = static_cast<int>(floor(blockPosition.y)) & (static_cast<int>(chunkSize)-1);
    int relZ = static_cast<int>(floor(blockPosition.z)) & (static_cast<int>(chunkSize)-1);

    return blockLayers[relY]->getBlockAt(relX, relZ);
}
