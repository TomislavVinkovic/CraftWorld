#include "ChunkMesh.h"

ChunkMesh::ChunkMesh() {
    VertexBufferLayout layout;
    // for now, only add position and texture positions
    layout.push<float>(3);
    layout.push<float>(2);

    m_Vao.addBuffers(m_Vbo, m_Ibo, layout);
}

void ChunkMesh::setIndices(const std::vector<unsigned int>& indices) {
    m_Vao.bind();
    m_Ibo.setData(indices);
}

void ChunkMesh::setVertices(const std::vector<float>& vertices) {
    m_Vao.bind();
    m_Vbo.setData(vertices);
}

void ChunkMesh::bind() const {
    m_Vao.bind();
    m_Ibo.bind();
}

void ChunkMesh::unbind() const {
    m_Vao.unbind();
}
