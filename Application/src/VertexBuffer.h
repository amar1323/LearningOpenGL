#pragma once
//size in bites

class VertexBuffer{
    private:
        unsigned int m_RenderedID;
    public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const ;
    void UnBind() const;
};