#include "BlockMesh.h"

BlockMesh::BlockMesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
: m_Vertices(vertices), m_Indices(indices), m_Vbo(vertices), m_Ibo(indices) {
    VertexBufferLayout layout;
    // for now, only add position and texture positions
    layout.push<float>(3);
    layout.push<float>(2);

    m_Vao.addBuffers(m_Vbo, m_Ibo, layout);
}
