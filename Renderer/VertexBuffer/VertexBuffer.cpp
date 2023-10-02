#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
    GLCall(glCreateBuffers(1, &m_VBO));
}

VertexBuffer::VertexBuffer(const std::vector<float>& data): VertexBuffer() {
    this->data = data;
    pushData();
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_VBO));
}

void VertexBuffer::addVec2(const glm::vec3 &vec) {
    data.insert(data.end(), { vec[0], vec[1] });
}

void VertexBuffer::addVec3(const glm::vec3 &vec) {
    data.insert(data.end(), { vec[0], vec[1], vec[2] });
}

void VertexBuffer::addVec4(const glm::vec3 &vec) {
    data.insert(data.end(), { vec[0], vec[1], vec[2], vec[3] });
}

void VertexBuffer::setData(const std::vector<float>& vertices) {
    data = vertices;
    pushData();
}

void VertexBuffer::pushData() const {
    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
}
void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}