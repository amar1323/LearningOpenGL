#pragma once

#include "VertexBuffer.h"

class VertexLayoutBuffer;

class VertexArray {
   private:
    unsigned int m_RendererID;
   public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;
    void AddBuffer(const VertexBuffer& vb, VertexLayoutBuffer layout);
};