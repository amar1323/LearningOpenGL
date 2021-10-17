#include "TestBlanc.h"

#include "GLFW/glfw3.h"
#include "VertexLayoutBuffer.h"
#include "imgui.h"

namespace test {

TestBlanc::TestBlanc() : m_TranslationA(200.0f, 0.0f, 0.0f),
                         m_TranslationB(100.0f, 0.0f, 0.0f),
                         m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
                         m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0))) {
    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f,  // 0
        200.0f, 100.0f, 1.0f, 0.0f,  // 1
        200.0f, 200.0f, 1.0f, 1.0f,  // 2
        100.0f, 200.0f, 0.0f, 1.0f   // 3
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VAO = std::make_unique<VertexArray>();
    m_IB = std::make_unique<IndexBuffer>(indices, 6);
    m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    m_Texture = std::make_unique<Texture>("/Users/amarelouazanituhami/Dev/LearningOpenGL/Application/res/textures/photo_coeur.png");
    m_Shader = std::make_unique<Shader>("/Users/amarelouazanituhami/Dev/LearningOpenGL/Application/res/shaders/Basic.shader");
    VertexLayoutBuffer layout;

    m_Shader->Bind();

    Renderer renderer;

    layout.push<float>(2);  //positions part
    layout.push<float>(2);  //texture part in vb
    m_VAO->AddBuffer(*m_VB, layout);

    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
}

TestBlanc::~TestBlanc() {
}

void TestBlanc::OnRender() {
    Renderer renderer;
    renderer.Clear();
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Proj * m_View * model;
        mvp = glm::rotate(mvp, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IB, *m_Shader);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IB, *m_Shader);
    }
}

void TestBlanc::OnImGuiRender() {
    ImGui::SliderFloat3("TranslationB", &m_TranslationA.x, 0.0f, 960.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::SliderFloat3("TranslationA", &m_TranslationB.x, 0.0f, 960.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}  // namespace test