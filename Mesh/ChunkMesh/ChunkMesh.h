#pragma once

#include "VertexArray/VertexArray.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"

struct ChunkMeshData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    ChunkMeshData() {
        indices = {};
        vertices = {};
    }

    ChunkMeshData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices):
        indices(indices), vertices(vertices) {}

};

class ChunkMesh {
    private:
        VertexArray m_Vao;
        VertexBuffer m_Vbo;
        IndexBuffer m_Ibo;

    public:
        ChunkMesh();
        ~ChunkMesh() = default;

        void setIndices(const std::vector<unsigned int>& indices);
        void setVertices(const std::vector<float>& vertices);

        const std::vector<unsigned int>& getIndices() const { return m_Ibo.getData(); }
        const std::vector<float>& getVertices() const { return m_Vbo.getData(); }

        void bind();
        void unbind();
};