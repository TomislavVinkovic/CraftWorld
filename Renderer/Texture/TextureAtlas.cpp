#include "TextureAtlas.h"
#include "stb_image/stb_image.h"

TextureAtlas::TextureAtlas(const std::string& path)
        : m_FilePath{path}, m_LocalBuffer{nullptr},
          m_Height{0}, m_Width{0}, m_BPP{0} {

    stbi_set_flip_vertically_on_load(1);

    // 4 je oznaka za broj kanala. Mi zelimo RGBA, pa imamo 4 kanala (3 kanala za boje plus alfa kanal)
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    GLCall(glGenTextures(1, &m_Texture));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    // set texture filtering parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

    this->unbind();

    if(m_LocalBuffer) {
        stbi_image_free(m_LocalBuffer);
    }
}


TextureAtlas::~TextureAtlas() {
    GLCall(glDeleteTextures(1, &m_Texture));
}

void TextureAtlas::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
}

void TextureAtlas::unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}