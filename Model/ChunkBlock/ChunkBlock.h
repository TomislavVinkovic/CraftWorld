#pragma once

#include "Block/ChunkBlockData.h"
#include "glm/glm.hpp"

class ChunkBlock {
    private:
        ChunkBlockType m_BlockType;

    public:
        ChunkBlock(ChunkBlockType blockType);

        // getters
        const ChunkBlockType getType() const { return m_BlockType; }
};
