#pragma once

#include <string>


class Texture {
   private:
    unsigned int m_RenderedID;
    std::string m_FilePatch;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

   public:
    Texture(const std::string path);
    ~Texture();

    void Bind(int slot = 0) const;
    void UnBind() const;
};