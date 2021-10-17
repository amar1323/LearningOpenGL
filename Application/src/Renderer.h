#pragma oncea

#include "GL/glew.h"


#define ASSERT(x) if(!(x)) asm("int $3");
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer{
    public:
    Renderer();
    ~Renderer();

    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

};