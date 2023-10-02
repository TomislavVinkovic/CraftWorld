# pragma once

#include <vector>

#include "VertexBufferLayout/VertexBufferLayout.h"
#include "GLDebug.h"

#include "glm/glm.hpp"

class VertexBuffer {
    private:
        std::vector<float> data{};
        unsigned int m_VBO;

        void pushData() const;
    public:
        VertexBuffer();
        explicit VertexBuffer(const std::vector<float>& data);
        ~VertexBuffer();

        void addVec2(const glm::vec3& vec);
        void addVec3(const glm::vec3& vec);
        void addVec4(const glm::vec3& vec);

        void setData(const std::vector<float>& vertices);

        void bind() const;
        void unbind() const;

        inline unsigned int getVBO() const { return m_VBO; }
        inline const std::vector<float>& getData() const { return data; }
};
