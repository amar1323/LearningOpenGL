#pragma once
//count in elements

class IndexBuffer{
    private:
        unsigned int m_RenderedID;
        unsigned int m_Count;
    public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;
    inline unsigned int GetCount() const { return m_Count; }
};