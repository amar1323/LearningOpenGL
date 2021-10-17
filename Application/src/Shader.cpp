#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Renderer.h"

enum class ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT
};

Shader::Shader(const std::string path) : m_File(path) {
    ShaderProgramSource source = ParseShader(path);
    m_RenderID = CreateShader(source.vertex, source.fragment);
}

Shader::~Shader() {
    GLCALL(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const {
    GLCALL(glUseProgram(m_RenderID));
}

void Shader::UnBind() const {
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string name, float value) {
    GLCALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string name, int value) {
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3) {
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string name, glm::mat4 mat) {
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

int Shader::GetUniformLocation(const std::string name) {
    if (m_LocationCache.find(name) != m_LocationCache.end())
        return m_LocationCache[name];
    GLCALL(int location = glGetUniformLocation(m_RenderID, name.c_str()));
    if (location == -1)
        std::cout << "warning! uniform " << name << " does not exists" << std::endl;
    m_LocationCache[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string path) {
    std::ifstream file;
    file.open(path);
    std::string line;
    std::stringstream ss[2];
    ShaderType type;
    while (getline(file, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else
            ss[(unsigned int)type] << line << std::endl;
        ;
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    GLCALL(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCALL(GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)));
        char *msg = (char *)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, msg));
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << msg << std::endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string vertex_shader, const std::string fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}