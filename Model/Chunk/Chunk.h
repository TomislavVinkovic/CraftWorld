#pragma once

#include <vector>
#include <cmath>
#include <cstdlib>
#include <memory>

#include "ChunkBlock/ChunkBlock.h"
#include "ChunkMesh/ChunkMesh.h"
#include "Chunk/ChunkBlockLayer/IChunkBlockLayer.h"

class Chunk {
    private:
        // flags
        bool isMeshed = false; // to be used later, when i implement the infinite world

        std::vector<std::shared_ptr<IChunkBlockLayer>> blockLayers;

        ChunkMesh m_ChunkMesh;
        glm::vec3 position;

    public:
        const static int chunkSize = 32;

        Chunk(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

        // getters
        const glm::vec3& getPosition() const { return position; }
        const std::vector<std::shared_ptr<IChunkBlockLayer>>& getBlockLayers() const { return blockLayers; }

        unsigned int getIndexCount() const { return m_ChunkMesh.getIndices().size(); }
        unsigned int getVertexCount() const { return m_ChunkMesh.getVertices().size(); }
        const ChunkMesh& getMesh() const { return m_ChunkMesh; }
        bool getIsMeshed() const { return isMeshed; }

        ChunkBlock getBlockAtPosition(const glm::vec3& blockPosition) const;

        glm::vec3 getRelativeBlockPositionFromIndex(int i) const;
        glm::vec3 getBlockPositionFromIndex(int i) const;

        // setters
        const inline glm::vec3& setPosition(glm::vec3 position) {
            this->position = position;
            return this->position;
        }
        void mesh(ChunkMeshData data);
        // void addBlock(ChunkBlockType type); // may be needed in the future

        void bind() const;
        void unbind() const;
};
