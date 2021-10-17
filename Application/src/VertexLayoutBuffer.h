#pragma once

#include <vector>

#include "GL/glew.h"
#include "Renderer.h"
struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static int getSizeOfType(unsigned int t) {
        switch (t) {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexLayoutBuffer {
   private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Strid;

   public:
    VertexLayoutBuffer() : m_Strid(0) {}
    void push(unsigned int count);
    template<typename T>
    void push(unsigned int count);

    inline std::vector<VertexBufferElement> getElements() { return m_Elements; }
    inline unsigned int getStrid() { return m_Strid; }
};

template <typename T>
void VertexLayoutBuffer::push(unsigned int count) {
    ASSERT(false);
}

template <>
inline void VertexLayoutBuffer::push<float>(unsigned int count) {
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Strid += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template <>
inline void VertexLayoutBuffer::push<unsigned int>(unsigned int count) {
    m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Strid += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void VertexLayoutBuffer::push<unsigned char>(unsigned int count) {
    m_Elements.push_back({GL_BYTE, count, GL_TRUE});
    m_Strid += count * VertexBufferElement::getSizeOfType(GL_BYTE);
}