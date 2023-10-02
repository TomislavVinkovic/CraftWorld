# pragma once

#include <vector>

#include "VertexBufferLayout/VertexBufferLayout.h"
#include "GLDebug.h"

#include "glm/glm.hpp"

class IndexBuffer {
private:
    std::vector<unsigned int> data{};
    unsigned int m_IBO;

    void pushData() const;

public:
    IndexBuffer();
    explicit IndexBuffer(const std::vector<unsigned int>& data);
    ~IndexBuffer();

    void addVec2(const glm::vec3& vec);
    void addVec3(const glm::vec3& vec);
    void addVec4(const glm::vec3& vec);

    void setData(const std::vector<unsigned int>& indices); //
    void bind() const;
    void unbind() const;

    inline unsigned int getIBO() const { return m_IBO; }
    inline const std::vector<unsigned int>& getData() const { return data; }
};
