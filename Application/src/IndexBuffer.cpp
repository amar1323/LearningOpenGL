#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_Count(count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCALL(glGenBuffers(1, &m_RenderedID))
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteRenderbuffers(1, &m_RenderedID));
}

void IndexBuffer::Bind() const{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID));
}

void IndexBuffer::UnBind() const{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}