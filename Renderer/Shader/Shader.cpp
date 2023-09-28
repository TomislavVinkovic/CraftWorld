#include "../../GLDebug/GLDebug.h"
#include "Shader.h"

Shader::Shader(const std::string& vs_FilePath, const std::string& fs_FilePath)
    : vs_FilePath{vs_FilePath}, fs_FilePath{fs_FilePath}, m_RendererId{0}
{
    auto vertexSource = parseShader(GL_VERTEX_SHADER);
    auto fragmentSource = parseShader(GL_FRAGMENT_SHADER);
    createShader(vertexSource, fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererId));
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(m_RendererId = glCreateProgram());
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    if(vs && fs) {
        GLCall(glAttachShader(m_RendererId, vs));
        GLCall(glAttachShader(m_RendererId, fs));
        GLCall(glLinkProgram(m_RendererId));
        GLCall(glValidateProgram(m_RendererId));

        // delete shader after the program has been compiled
        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return m_RendererId;
    }
    else {
        return 0;
    }
}

std::string Shader::parseShader(unsigned int type) {
    std::string filePath;
    if(type == GL_VERTEX_SHADER) {
        filePath = vs_FilePath;
    }
    else if(type == GL_FRAGMENT_SHADER) {
        filePath = fs_FilePath;
    }
    std::ifstream stream(filePath);

    std::string line;
    std::stringstream ss;

    while( getline(stream, line) ) {
        ss << line << '\n';
    }

    return ss.str();
}

unsigned int Shader::compileShader(const std::string& source, unsigned int type) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* message = (char*) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "---Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  <<" shader----" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

void Shader::bind() const {
    GLCall(glUseProgram(m_RendererId));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCall(int location = getUniformLocation(name));
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::setUniform3f(const std::string &name, float v0, float v1, float v2) {
    GLCall(int location = getUniformLocation(name));
    GLCall(glUniform3f(location, v0, v1, v2));
}

void Shader::setUniform1f(const std::string &name, float value) {
    GLCall(int location = getUniformLocation(name));
    GLCall(glUniform1f(location, value));
}

void Shader::setUniform1i(const std::string &name, int value) {
    GLCall(int location = getUniformLocation(name));
    GLCall(glUniform1i(location, value));
}

void Shader::setUniformMat3f(const std::string& name, const glm::mat3& matrix) {
    GLCall(int location = getUniformLocation(name));
    GLCall(glad_glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]))
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    GLCall(int location = getUniformLocation(name));
    GLCall(glad_glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]))
}

int Shader::getUniformLocation(const std::string &name) {
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    const char* uniformName = name.c_str();
    GLCall(int location = glGetUniformLocation(m_RendererId, uniformName));
    if(location == -1) {
        std::cout << "Warning: uniform " << name << " does not exist" << std::endl;
    }
    else {
        m_UniformLocationCache[name] = location;
    }
    return location;
}

