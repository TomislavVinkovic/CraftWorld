# pragma once

#include "ChunkMesh/ChunkMesh.h"
#include "Chunk/Chunk.h"

/*
 * This class is used to generate a mesh for a chunk once its terrain has been generated
 */
class ChunkMeshGenerator {
    public:
        ChunkMeshGenerator() = default;

        void mesh(Chunk& chunk) const;
        void addFace(
                Chunk& chunk,
                const ChunkBlock& block,
                const glm::vec3& blockPosition,
                std::vector<float>& vertices,
                std::vector<unsigned int>& indices,
                const glm::vec3& adjacentBlockPosition,
                const std::vector<float>& faceVertices,
                const std::vector<float>& texCoords,
                unsigned int& currentVIndex
        ) const;
};