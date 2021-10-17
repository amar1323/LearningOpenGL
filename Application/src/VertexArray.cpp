#include "VertexArray.h"
#include "VertexLayoutBuffer.h"

VertexArray::VertexArray() {
    GLCALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const{
    GLCALL(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const{
    GLCALL(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, VertexLayoutBuffer layout) {
    Bind();
    vb.Bind();
    unsigned  int offset = 0;
    for (int i = 0; i < layout.getElements().size(); i++) {
        VertexBufferElement& element = layout.getElements()[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStrid(), (void *)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
