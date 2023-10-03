#include "Chunk.h"

Chunk::Chunk(glm::vec3 position): position(position) {
    std::srand(static_cast<unsigned int>(time(nullptr)));

    // Define the range
    int min = 0;
    int max = 12;
    int type = std::rand() % (max - min + 1) + min;
    // pushing back 32^3 blocks
    int z, x, y;
    for(int i = 0; i < pow(chunkSize, 3); i++) {
        blocks.push_back(ChunkBlock(static_cast<ChunkBlockType>(type)));
    }
}

void Chunk::addBlock(ChunkBlockType type) {
    blocks.push_back(ChunkBlock(type));
}

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

    int offset = relX + chunkSize * (relY + chunkSize * relZ);
    return blocks[offset];
}

glm::vec3 Chunk::getBlockPositionFromIndex(int i) const {
    int z = position.z +  i / (32 * 32);
    int y = position.y + (i % (32 * 32)) / 32;
    int x = position.x + (i % (32 * 32)) % 32;

    return {x, y, z};
}
