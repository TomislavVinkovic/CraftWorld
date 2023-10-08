#pragma once

#include "Chunk/IChunk/IChunk.h"

class SingleBlockTypeChunk: public IChunk {
    private:
        ChunkBlock block; // the only block information that i need
    public:
        SingleBlockTypeChunk(ChunkBlockType block, const glm::vec3& position = {0.f, 0.f, 0.f});
        ~SingleBlockTypeChunk() = default;

        ChunkBlock getBlockAtPosition(const glm::vec3 &blockPosition) const override;
};
