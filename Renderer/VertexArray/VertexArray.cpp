#include "VertexArray.h"

VertexArray::VertexArray() {
    GLCall(glCreateVertexArrays(1, &m_VAO));
}

VertexArray::VertexArray(
        const VertexBuffer &vbo,
        const IndexBuffer &ibo,
        const VertexBufferLayout &layout
): VertexArray() {
    addBuffers(vbo, ibo, layout);
}

VertexArray::~VertexArray() {
    std::cout << m_VAO << std::endl;
    GLCall(glDeleteVertexArrays(1, &m_VAO));
}

void VertexArray::addBuffers(const VertexBuffer &vbo, const IndexBuffer &ibo, const VertexBufferLayout &layout) {
    bind();
    vbo.bind();

    unsigned int offset = 0;

    const auto& elements = layout.getElements();
    for(int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }

    ibo.bind();
}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(m_VAO));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}
