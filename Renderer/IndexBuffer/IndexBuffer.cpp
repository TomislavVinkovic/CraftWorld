#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() {
    GLCall(glCreateBuffers(1, &m_IBO));
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data): IndexBuffer() {
    this->data = data;
    pushData();
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_IBO));
}

void IndexBuffer::addVec2(const glm::vec3 &vec) {
    data.insert(data.end(), { static_cast<unsigned int>(vec[0]), static_cast<unsigned int>(vec[1]) });
}

void IndexBuffer::addVec3(const glm::vec3 &vec) {
    data.insert(data.end(), { static_cast<unsigned int>(vec[0]), static_cast<unsigned int>(vec[1]), static_cast<unsigned int>(vec[2]) });
}

void IndexBuffer::addVec4(const glm::vec3 &vec) {
    data.insert(data.end(), { static_cast<unsigned int>(vec[0]), static_cast<unsigned int>(vec[1]), static_cast<unsigned int>(vec[2]), static_cast<unsigned int>(vec[3]) });
}

void IndexBuffer::setData(const std::vector<unsigned int>& indices) {
    data = indices;
    pushData();
}

void IndexBuffer::pushData() const {
    bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
}
void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}