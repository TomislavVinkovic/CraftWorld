# pragma once

#include "GLDebug.h"
#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT: return 4; break;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
            : m_Stride{0} {}

    template<typename T>
    void push(unsigned int count, bool normalized=false);

    // getters
    inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
    inline const unsigned int getStride() const { return m_Stride; }
};

template<>
inline void VertexBufferLayout::push<float>(unsigned int count, bool normalized) {
    m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    m_Elements.push_back({GL_FLOAT, count, normalized });
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count, bool normalized) {
    m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    m_Elements.push_back({GL_UNSIGNED_INT, count, normalized });
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count, bool normalized) {
    m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    m_Elements.push_back({GL_UNSIGNED_BYTE, count, normalized });
}