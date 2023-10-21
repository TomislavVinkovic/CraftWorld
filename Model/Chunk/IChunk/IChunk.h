#pragma once

#include "ChunkMesh/ChunkMesh.h"
#include "glm/glm.hpp"
#include "ChunkBlock/ChunkBlock.h"

#include <memory>

/* Abstract class, can be either a real chunk, or a hollow chunk
 * using a single block type (saves memory)
*/

class IChunk {
    public:

        ChunkMeshData meshData;

        bool isGenerated = false;
        bool isFlaggedForRemeshing = false;
        bool isMeshed = false; // to be used later, when i implement the infinite world
    protected:
        std::shared_ptr<ChunkMesh> m_ChunkMesh;
        glm::vec3 position;
    public:
        const static int chunkSize = 32;

        // getters
        const glm::vec3& getPosition() const { return position; }
        unsigned int getIndexCount() const { return m_ChunkMesh == nullptr ? 0 : m_ChunkMesh->getIndices().size(); }
        unsigned int getVertexCount() const { return m_ChunkMesh == nullptr ? 0 : m_ChunkMesh->getVertices().size(); }
        std::shared_ptr<ChunkMesh> getMesh() const { return m_ChunkMesh; }


        virtual ChunkBlock getBlockAtPosition(const glm::vec3& blockPosition) const = 0;

        glm::vec3 getRelativeBlockPositionFromIndex(int i) const;
        glm::vec3 getBlockPositionFromIndex(int i) const;

        // setters
        const inline glm::vec3& setPosition(glm::vec3 position) {
            this->position = position;
            return this->position;
        }
        void applyMesh();
        void setData(const ChunkMeshData& data);

        // opengl bindings
        void bind() const;
        void unbind() const;
};