#pragma once

#include "../../GLDebug/GLDebug.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"

#include <unordered_map>

class Shader {
    private:
        std::string vs_FilePath;
        std::string fs_FilePath;

        unsigned int m_RendererId;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        // caching for uniforms
    public:
        Shader(const std::string& vs_FilePath, const std::string& fs_FilePath);
        ~Shader();

        void bind() const;
        void unbind() const;

        // set uniforms
        void setUniform1i(const std::string& name, int value);
        void setUniform1f(const std::string& name, float value);

        void setUniform3f(const std::string &name, float v0, float v1, float v2);
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

        void setUniformMat3f(const std::string& name, const glm::mat3& matrix);
        void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
        std::string parseShader(unsigned int type);
        unsigned int compileShader(const std::string& source, unsigned int type);
        int getUniformLocation(const std::string& name);
};