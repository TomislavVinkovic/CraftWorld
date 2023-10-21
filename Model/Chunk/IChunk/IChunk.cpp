//
// Created by tomislav on 10/4/23.
//

#include "IChunk.h"

glm::vec3 IChunk::getRelativeBlockPositionFromIndex(int i) const {
    int z = i / (chunkSize * chunkSize);
    int y = (i % (chunkSize * IChunk::chunkSize)) / chunkSize;
    int x = (i % (chunkSize * chunkSize)) % chunkSize;

    return {x, y, z};
}


glm::vec3 IChunk::getBlockPositionFromIndex(int i) const {
    int z = position.z +  i / (chunkSize * chunkSize);
    int y = position.y + (i % (chunkSize * chunkSize)) / chunkSize;
    int x = position.x + (i % (chunkSize * chunkSize)) % chunkSize;

    return {x, y, z};
}

void IChunk::setData(const ChunkMeshData& data) {
    meshData = data;
}

void IChunk::applyMesh() {
    m_ChunkMesh = std::make_shared<ChunkMesh>();
    // set the "isMeshed" flag to true

    // add vertices and indices to the mesh
    m_ChunkMesh->setIndices(meshData.indices);
    m_ChunkMesh->setVertices(meshData.vertices);
    meshData = {}; // clear the mesh data from here since it is copied to the mesh

    isMeshed = true;
}

void IChunk::bind() const {
    if(m_ChunkMesh != nullptr) {
        m_ChunkMesh->bind();
    }
}

void IChunk::unbind() const {
    if(m_ChunkMesh == nullptr) {
        m_ChunkMesh->unbind();
    }
}
