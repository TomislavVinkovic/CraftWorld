#pragma once

#include "GLDebug.h"

class TextureAtlas {
private:
    unsigned int m_Texture;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer; // texture storage on the cpu side

    // BPP stands for Bits Per Pixel
    int m_Width, m_Height, m_BPP;
public:
    TextureAtlas(const std::string& path);
    ~TextureAtlas();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }
};