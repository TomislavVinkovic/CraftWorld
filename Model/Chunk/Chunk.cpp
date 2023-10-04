#include "Chunk.h"
#include "Chunk/ChunkBlockLayer/SingleBlockChunkBlockLayer.h"
#include "Chunk/ChunkBlockLayer/ChunkBlockLayer/ChunkBlockLayer.h"

Chunk::Chunk(glm::vec3 position): position(position) {

    // select a random block type for the chunk
    std::srand(static_cast<unsigned int>(time(nullptr)));
    // Define the range
    int min = 0;
    int max = 12;
    int type = std::rand() % (max - min + 1) + min;

    // check if the chunk consists of a single block type
    // and if it is solid
    bool areBlocksSame = true;
    bool areBlocksSolid = true;
    for(int y = 0; y < chunkSize; y++) {
        std::vector<ChunkBlock> blocks;
        ChunkBlockType prevBlockType;

        for(int i = 0; i < pow(chunkSize, 2); i++) {
            blocks.push_back(ChunkBlock(static_cast<ChunkBlockType>(type)));
            if(i == 0) {
                prevBlockType = blocks[0].getType();
            }
            auto& blockData = block_type_data::getBlockDataByType(blocks.back().getType());
            if(areBlocksSolid && !blockData.isSolid) {
                areBlocksSolid = false;
            }
            if(areBlocksSame && blocks.back().getType() != prevBlockType) {
                areBlocksSame = false;
            }
            prevBlockType = blocks.back().getType();
        }

        // if it consists of a single block type, we can store that layer as a single block, to save memory
        if(areBlocksSame) {
            blockLayers.push_back(std::make_shared<SingleBlockChunkBlockLayer>(blocks[0], y));
        }

        // otherwise, we have to save information about all blocks
        else {
            blockLayers.push_back(std::make_shared<ChunkBlockLayer>(blocks, y));
        }

        // if the entire block layer is solid, mark it as such
        blockLayers.back()->setIsSolid(areBlocksSolid);
    }
}

// may be needed in the future
//void Chunk::addBlock(ChunkBlockType type) {
//    blocks.push_back(ChunkBlock(type));
//}

void Chunk::mesh(ChunkMeshData data) {
    // set the "isMeshed" flag to true
    isMeshed = true;

    // add vertices and indices to the mesh
    m_ChunkMesh.setIndices(data.indices);
    m_ChunkMesh.setVertices(data.vertices);
}

void Chunk::bind() const {
    m_ChunkMesh.bind();
}

void Chunk::unbind() const {
    m_ChunkMesh.unbind();
}

ChunkBlock Chunk::getBlockAtPosition(const glm::vec3& blockPosition) const {
    bool containedInX = blockPosition.x >= position.x && blockPosition.x < position.x + chunkSize;
    bool containedInY = blockPosition.y >= position.y && blockPosition.y < position.y + chunkSize;
    bool containedInZ = blockPosition.z >= position.z && blockPosition.z < position.z + chunkSize;

    if(
            !containedInX || !containedInY || !containedInZ
            ) {
        return {ChunkBlockType::Air};
    }

    int relX = static_cast<int>(floor(blockPosition.x)) & (static_cast<int>(chunkSize)-1);
    int relY = static_cast<int>(floor(blockPosition.y)) & (static_cast<int>(chunkSize)-1);
    int relZ = static_cast<int>(floor(blockPosition.z)) & (static_cast<int>(chunkSize)-1);


    return blockLayers[relY]->getBlockAt(relX, relZ);
}

glm::vec3 Chunk::getRelativeBlockPositionFromIndex(int i) const {
    int z = i / (Chunk::chunkSize * Chunk::chunkSize);
    int y = (i % (Chunk::chunkSize * Chunk::chunkSize)) / Chunk::chunkSize;
    int x = (i % (Chunk::chunkSize * Chunk::chunkSize)) % Chunk::chunkSize;

    return {x, y, z};
}


glm::vec3 Chunk::getBlockPositionFromIndex(int i) const {
    int z = position.z +  i / (Chunk::chunkSize * Chunk::chunkSize);
    int y = position.y + (i % (Chunk::chunkSize * Chunk::chunkSize)) / Chunk::chunkSize;
    int x = position.x + (i % (Chunk::chunkSize * Chunk::chunkSize)) % Chunk::chunkSize;

    return {x, y, z};
}
