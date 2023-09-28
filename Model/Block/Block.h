#pragma once

#include "Block/ChunkBlockData.h"
#include "glm/glm.hpp"
#include "BlockMesh/BlockMesh.h"

class Block {
    private:
        ChunkBlockType m_BlockType;
        BlockMesh* m_BlockMesh = nullptr;
        glm::vec3 position{0.f, 0.f, 0.f};

    public:
        Block(ChunkBlockType blockType);

        // getters
        const glm::vec3& getPosition() { return position; }

        void bind();
        void unbind();
};
