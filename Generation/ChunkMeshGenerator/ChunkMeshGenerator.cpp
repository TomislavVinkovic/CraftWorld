#include <vector>

#include "ChunkMeshGenerator.h"
#include "Block/ChunkBlockData.h"
#include "AdjacentChunkBlockPositions.h"
#include "AdjacentChunkPositions.h"

#include "fmt/core.h"

void ChunkMeshGenerator::mesh(std::shared_ptr<Chunk> chunk, bool remeshNeighboringChunks) {
    unsigned int currentVIndex = 0;

    // I will pass these vector objects to the faces generator by refference
    ChunkMeshData meshData;

    const auto& blocks = chunk->getBlocks();
    const auto& chunkPosition = chunk->getPosition();
    AdjacentChunkBlockPositions adjacentChunkBlockPositions;
    AdjacentChunkPositions adjacentChunkPositions;

    adjacentChunkPositions.update(
            chunkPosition.x, chunkPosition.y, chunkPosition.z
    );
    if(remeshNeighboringChunks) {
        for(auto& pos: adjacentChunkPositions.getPositions()) {
            std::string posKey = fmt::format("{} {} {}", pos.x, pos.y, pos.z);
            auto chunkIter = m_WorldChunks.find(posKey);
            if(chunkIter != m_WorldChunks.end() && toRemesh.find(posKey) == toRemesh.end()) {
                toRemesh[posKey] = chunkIter->second;
            }
        }
    }


    for(int i = 0; i < blocks.size(); i++) {
        const auto& chunkBlock = blocks[i];
        const auto& chunkBlockData = block_type_data::getBlockDataByType(chunkBlock.getType());
        // there are surely no indices to be rendered with an air block
        if(chunkBlock.getType() == ChunkBlockType::Air) continue;

        // get the block postion and update the neighbouring positions accordingly
        const auto blockPosition = chunk->getBlockPositionFromIndex(i);
        adjacentChunkBlockPositions.update(
                static_cast<int>(blockPosition.x),
                static_cast<int>(blockPosition.y),
                static_cast<int>(blockPosition.z)
        );

        // back face
        addFace(
            chunk,
            chunkBlock,
            blockPosition,
            meshData.vertices,
            meshData.indices,
            adjacentChunkBlockPositions.back,
            adjacentChunkPositions.back,
            block_data::backFace,
            chunkBlockData.backFaceTexCoords,
            currentVIndex
        );

        // front face
        addFace(
            chunk,
            chunkBlock,
            blockPosition,
            meshData.vertices,
            meshData.indices,
            adjacentChunkBlockPositions.front,
            adjacentChunkPositions.front,
            block_data::frontFace,
            chunkBlockData.frontFaceTexCoords,
            currentVIndex
        );

        // right face
        addFace(
            chunk,
            chunkBlock,
            blockPosition,
            meshData.vertices,
            meshData.indices,
            adjacentChunkBlockPositions.right,
            adjacentChunkPositions.right,
            block_data::rightFace,
            chunkBlockData.rightFaceTexCoords,
            currentVIndex
        );

        // left face
        addFace(
            chunk,
            chunkBlock,
            blockPosition,
            meshData.vertices,
            meshData.indices,
            adjacentChunkBlockPositions.left,
            adjacentChunkPositions.left,
            block_data::leftFace,
            chunkBlockData.leftFaceTexCoords,
            currentVIndex
        );

        // top face
        addFace(
            chunk,
            chunkBlock,
            blockPosition,
            meshData.vertices,
            meshData.indices,
            adjacentChunkBlockPositions.top,
            adjacentChunkPositions.top,
            block_data::topFace,
            chunkBlockData.topFaceTexCoords,
            currentVIndex
        );

        // bottom face
        addFace(
            chunk,
            chunkBlock,
            blockPosition,
            meshData.vertices,
            meshData.indices,
            adjacentChunkBlockPositions.bottom,
            adjacentChunkPositions.bottom,
            block_data::bottomFace,
            chunkBlockData.bottomFaceTexCoords,
            currentVIndex
        );
    }

    chunk->mesh(meshData);
}

void ChunkMeshGenerator::addFace(
        std::shared_ptr<Chunk> chunk,
        const ChunkBlock& block,
        const glm::vec3& blockPosition,
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices,
        const glm::vec3& adjacentBlockPosition,
        const glm::vec3& adjacentChunkPosition,
        const std::vector<float>& faceVertices,
        const std::vector<float>& texCoords,
        unsigned int& currentVIndex
) {
    const auto& neighbouringBlock = chunk->getBlockAtPosition(adjacentBlockPosition);
    const auto& chunkPosition = chunk->getPosition();
    // if the neighbouring block is not solid, then add the face to the mesh
    const auto& blockData = block_type_data::getBlockDataByType(neighbouringBlock.getType());

    bool isNeighboringBlockSolid = blockData.isSolid;
    if(!isNeighboringBlockSolid) {
        // if the neighbouring block is an air block, but the block is
        // at an edge of a chunk, check the block in the neighbouring chunk
        std::string key = fmt::format(
                "{} {} {}",
                adjacentChunkPosition.x,
                adjacentChunkPosition.y,
                adjacentChunkPosition.z
        );
        auto neighbouringChunkIter = m_WorldChunks.find(key);
        if(neighbouringChunkIter != m_WorldChunks.end()) {
            auto neighbouringChunkBlock = neighbouringChunkIter->second->getBlockAtPosition(adjacentBlockPosition);
            auto& neighbouringChunkBlockData = block_type_data::getBlockDataByType(neighbouringChunkBlock.getType());
            isNeighboringBlockSolid = neighbouringChunkBlockData.isSolid;
        }

        if(!isNeighboringBlockSolid) {
            for(int i = 0, j = 0, k = 0; i < 4; i++) {
                // block position data
                vertices.push_back(faceVertices[j++] + blockPosition.x);
                vertices.push_back(faceVertices[j++] + blockPosition.y);
                vertices.push_back(faceVertices[j++] + blockPosition.z);

                // block texture coordinates data
                vertices.push_back(texCoords[k++]); // s
                vertices.push_back(texCoords[k++]); // t
            }

            // indices for the 2 added triangles
            indices.insert(indices.end(), {
                    currentVIndex, currentVIndex + 1, currentVIndex + 2,
                    currentVIndex + 2, currentVIndex + 3, currentVIndex,
            });
            currentVIndex += 4;
        }
    }
}