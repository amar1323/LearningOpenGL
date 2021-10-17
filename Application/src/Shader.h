#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource {
    std::string vertex;
    std::string fragment;
};

class Shader {
   public:
    Shader(const std::string path);
    ~Shader();

    void SetUniform1i(const std::string name, int value);
    void SetUniform1f(const std::string name, float value);
    void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string name, glm::mat4 mat);
    void Bind() const;
    void UnBind() const;

   private:
    unsigned int m_RenderID;

    std::string m_File;
    std::unordered_map<std::string, int> m_LocationCache;
    int GetUniformLocation(const std::string);
    ShaderProgramSource ParseShader(std::string path);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string vertex_shader, const std::string fragment_shader);
};