#include <vector>

#include "ChunkMeshGenerator.h"
#include "Block/ChunkBlockData.h"
#include "AdjacentChunkBlockPositions.h"

void ChunkMeshGenerator::mesh(Chunk &chunk) const {
    unsigned int currentVIndex = 0;

    // I will pass these vector objects to the faces generator by refference
    ChunkMeshData meshData;

    const auto& blocks = chunk.getBlocks();
    const auto& chunkPosition = chunk.getPosition();
    AdjacentChunkBlockPositions adjacentChunkBlockPositions;

    for(int i = 0; i < blocks.size(); i++) {
        const auto& chunkBlock = blocks[i];
        const auto& chunkBlockData = block_type_data::getBlockDataByType(chunkBlock.getType());
        // there are surely no indices to be rendered with an air block
        if(chunkBlock.getType() == ChunkBlockType::Air) continue;

        // get the block postion and update the neighbouring positions accordingly
        const auto blockPosition = chunk.getBlockPositionFromIndex(i);
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
            block_data::bottomFace,
            chunkBlockData.bottomFaceTexCoords,
            currentVIndex
        );
    }

    chunk.mesh(meshData);
}

void ChunkMeshGenerator::addFace(
        Chunk& chunk,
        const ChunkBlock& block,
        const glm::vec3& blockPosition,
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices,
        const glm::vec3& adjacentBlockPosition,
        const std::vector<float>& faceVertices,
        const std::vector<float>& texCoords,
        unsigned int& currentVIndex
) const {
    const auto& neighbouringBlock = chunk.getBlockAtPosition(adjacentBlockPosition);
    
    // if the neighbouring block is not solid, then add the face to the mesh
    const auto& blockData = block_type_data::getBlockDataByType(neighbouringBlock.getType());
    if(!blockData.isSolid) {
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
