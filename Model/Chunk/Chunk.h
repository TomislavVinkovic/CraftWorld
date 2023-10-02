#pragma once

#include <vector>
#include <cmath>

#include "ChunkBlock/ChunkBlock.h"
#include "ChunkMesh/ChunkMesh.h"

class Chunk {
    private:
        // flags
        bool isMeshed = false; // to be used later, when i implement the infinite world

        std::vector<ChunkBlock> blocks;
        ChunkMesh m_ChunkMesh;
        glm::vec3 position;

    public:
        const int chunkSize = 32;

        Chunk(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

        // getters
        const glm::vec3& getPosition() const { return position; }
        const std::vector<ChunkBlock>& getBlocks() const { return blocks; }

        unsigned int getIndexCount() const { return m_ChunkMesh.getIndices().size(); }
        unsigned int getVertexCount() const { return m_ChunkMesh.getVertices().size(); }

        ChunkBlock getBlockAtPosition(const glm::vec3& blockPosition) const;
        glm::vec3 getBlockPositionFromIndex(int i) const;

        // setters
        void mesh(ChunkMeshData data);

        void bind();
        void unbind();
};
