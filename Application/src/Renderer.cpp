#include "Renderer.h"

#include <iostream>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
void GLClearError() {
    while (glGetError() != GL_NO_ERROR)
        ;
};

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] ("
                  << "0x0" << std::hex << error << ")"
                  << " " << function << " " << file << ":" << std::dec << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::Clear() {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
