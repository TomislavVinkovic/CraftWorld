#pragma once

#include "GLDebug.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"

class VertexArray {
    private:
        unsigned int m_VAO;
    public:
        VertexArray();
        VertexArray(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexBufferLayout& layout);
        ~VertexArray();

        void addBuffers(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexBufferLayout& layout);

        void bind() const;
        void unbind() const;
};
