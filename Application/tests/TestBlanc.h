#pragma once

#include <memory>

#include "IndexBuffer.h"
#include "Shader.h"
#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

class TestBlanc : public Test {
   public:
    TestBlanc();
    ~TestBlanc();
    void OnRender() override;
    void OnImGuiRender() override;

   private:
    glm::mat4 m_Proj, m_View;

    glm::vec3 m_TranslationA, m_TranslationB;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<IndexBuffer> m_IB;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<VertexBuffer> m_VB;
    std::unique_ptr<Texture> m_Texture;
};
}  // namespace test