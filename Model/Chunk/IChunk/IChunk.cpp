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

void IChunk::mesh(ChunkMeshData data) {
    // set the "isMeshed" flag to true
    isMeshed = true;

    // add vertices and indices to the mesh
    m_ChunkMesh.setIndices(data.indices);
    m_ChunkMesh.setVertices(data.vertices);
}

void IChunk::bind() const {
    m_ChunkMesh.bind();
}

void IChunk::unbind() const {
    m_ChunkMesh.unbind();
}
