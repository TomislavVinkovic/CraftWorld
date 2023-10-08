#include "SingleBlockTypeChunk.h"

SingleBlockTypeChunk::SingleBlockTypeChunk(ChunkBlockType type, const glm::vec3 &position): block(type) {
    this->position = position;
}

ChunkBlock SingleBlockTypeChunk::getBlockAtPosition(const glm::vec3 &blockPosition) const {
    bool containedInX = blockPosition.x >= position.x && blockPosition.x < position.x + chunkSize;
    bool containedInY = blockPosition.y >= position.y && blockPosition.y < position.y + chunkSize;
    bool containedInZ = blockPosition.z >= position.z && blockPosition.z < position.z + chunkSize;


    // default behavior: return air block
    if(
            !containedInX || !containedInY || !containedInZ
            ) {
        return ChunkBlock(ChunkBlockType::Air);
    }

    return block;
}
