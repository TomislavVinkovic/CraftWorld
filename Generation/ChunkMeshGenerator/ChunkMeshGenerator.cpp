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

    for(int i = 0; i < pow(Chunk::chunkSize, 3); i++) {
        const auto& chunkBlock = chunk->getBlockAtPosition(chunk->getBlockPositionFromIndex(i));
        const auto& chunkBlockData = block_type_data::getBlockDataByType(chunkBlock.getType());
        // there are surely no indices to be rendered with an air block
        if(chunkBlock.getType() == ChunkBlockType::Air) continue;

        // get the block postion and update the neighbouring positions accordingly
        const auto blockPosition = chunk->getBlockPositionFromIndex(i);
        const auto relativeBlockPosition = chunk->getRelativeBlockPositionFromIndex(i);

        adjacentChunkBlockPositions.update(
                static_cast<int>(blockPosition.x),
                static_cast<int>(blockPosition.y),
                static_cast<int>(blockPosition.z)
        );

        std::shared_ptr<IChunkBlockLayer>
                layerAbove = nullptr, layerBelow = nullptr, layerFront = nullptr,
                layerBack = nullptr, layerLeft = nullptr, layerRight = nullptr;

        int layerAboveY = static_cast<int>(blockPosition.y) % 32 + 1;
        int layerBelowY = static_cast<int>(blockPosition.y) % 32 - 1;
        int sideLayerY = static_cast<int>(blockPosition.y) % 32;

        if(layerAboveY >= 0 && layerAboveY < 32) {
            layerAbove = chunk->getBlockLayers()[layerAboveY];
            if(layerAbove == nullptr) {
                auto upperChunkPos = fmt::format("{} {} {}", chunkPosition.x, chunkPosition.y + 1, chunkPosition.z);
                auto chunkIter = m_WorldChunks.find(upperChunkPos);
                if(chunkIter != m_WorldChunks.end()) {
                    layerAbove = chunkIter->second->getBlockLayers()[layerAboveY];
                }
            }
        }

        if(layerBelowY >= 0 && layerBelowY < 32) {
            layerBelow = chunk->getBlockLayers()[layerBelowY];
            if(layerBelow == nullptr) {
                auto lowerChunkPos = fmt::format("{} {} {}", chunkPosition.x, chunkPosition.y - 1, chunkPosition.z);
                auto chunkIter = m_WorldChunks.find(lowerChunkPos);
                if(chunkIter != m_WorldChunks.end()) {
                    layerBelow = chunkIter->second->getBlockLayers()[layerBelowY];
                }
            }
        }

        if(sideLayerY >= 0 && sideLayerY < 32) {
            auto frontChunkPos =
                    fmt::format("{} {} {}", chunkPosition.x, chunkPosition.y, chunkPosition.z-1);
            auto backChunkPos =
                    fmt::format("{} {} {}", chunkPosition.x, chunkPosition.y, chunkPosition.z+1);
            auto leftChunkPos =
                    fmt::format("{} {} {}", chunkPosition.x - 1, chunkPosition.y, chunkPosition.z);
            auto rightChunkPos =
                    fmt::format("{} {} {}", chunkPosition.x + 1, chunkPosition.y, chunkPosition.z);

            auto frontChunkIter = m_WorldChunks.find(frontChunkPos);
            auto backChunkIter = m_WorldChunks.find(backChunkPos);
            auto leftChunkIter = m_WorldChunks.find(leftChunkPos);
            auto rightChunkIter = m_WorldChunks.find(rightChunkPos);

            if(frontChunkIter != m_WorldChunks.end()) {
                layerFront = frontChunkIter->second->getBlockLayers()[sideLayerY];
            }
            if(backChunkIter != m_WorldChunks.end()) {
                layerBack = backChunkIter->second->getBlockLayers()[sideLayerY];
            }
            if(leftChunkIter != m_WorldChunks.end()) {
                layerLeft = leftChunkIter->second->getBlockLayers()[sideLayerY];
            }
            if(rightChunkIter != m_WorldChunks.end()) {
                layerRight = rightChunkIter->second->getBlockLayers()[sideLayerY];
            }
        }

        // back face
        if(layerBack == nullptr || !layerBack->getIsSolid()) {
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
        }


        // front face
        if(layerFront == nullptr || !layerFront->getIsSolid()) {
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
        }

        // right face
        if(layerRight == nullptr || !layerRight->getIsSolid()) {
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
        }

        // left face
        if(layerLeft == nullptr || !layerLeft->getIsSolid()) {
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
        }

        // top face
        if(layerAbove == nullptr || !layerAbove->getIsSolid()) {
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
        }

        // bottom face
        if(layerBelow == nullptr || !layerBelow->getIsSolid()) {
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