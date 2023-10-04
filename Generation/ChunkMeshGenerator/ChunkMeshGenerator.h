# pragma once

#include "ChunkMesh/ChunkMesh.h"
#include "Chunk/Chunk.h"

#include <unordered_map>

/*
 * This class is used to generate a mesh for a chunk once its terrain has been generated
 */
class ChunkMeshGenerator {
    private:
        std::unordered_map<std::string, Chunk>* m_WorldChunks = nullptr;
        std::unordered_map<std::string, std::unordered_map<std::string, Chunk>::iterator> toRemesh;
    public:
        ChunkMeshGenerator() = default;

        void mesh(Chunk& chunk, bool remeshNeighboringChunks = true);
        void addFace(
                Chunk& chunk,
                const ChunkBlock& block,
                const glm::vec3& blockPosition,
                std::vector<float>& vertices,
                std::vector<unsigned int>& indices,
                const glm::vec3& adjacentBlockPosition,
                const glm::vec3& adjacentChunkPosition,
                const std::vector<float>& faceVertices,
                const std::vector<float>& texCoords,
                unsigned int& currentVIndex
        );

        void setWorldChunks(std::unordered_map<std::string, Chunk>& worldChunks) { this->m_WorldChunks = &worldChunks; }
        inline const std::unordered_map<std::string, std::unordered_map<std::string, Chunk>::iterator>& getToRemeshTable() const { return toRemesh; };
        inline const std::unordered_map<std::string, std::unordered_map<std::string, Chunk>::iterator>& clearToRemeshTable() { toRemesh = {}; };
};