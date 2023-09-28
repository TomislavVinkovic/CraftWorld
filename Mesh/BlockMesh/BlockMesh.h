#include <vector>

#include "GLDebug.h"
#include "VertexArray/VertexArray.h"

class BlockMesh {
    private:
        VertexArray m_Vao;
        VertexBuffer m_Vbo;
        IndexBuffer m_Ibo;

        std::vector<float> m_Vertices;
        std::vector<unsigned int> m_Indices;
    public:
        BlockMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        ~BlockMesh() = default;

        // getters
        const std::vector<float>& getVertices() const { return m_Vertices; }
        const std::vector<unsigned int>& getIndices() const { return m_Indices; }
        const VertexArray& getVao() { return m_Vao; }
};
