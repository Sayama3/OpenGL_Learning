//
// Created by Sayama on 23/02/2023.
//

#include <iostream>
#include "ShaderProgram.hpp"
#include "Renderer.hpp"
#include "ShaderType.hpp"

namespace Sayama::OpenGLLearning {
    ShaderProgram::ShaderProgram(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
    : m_RendererId(0), m_UniformLocationCache()
    {
        Shader vertexShader(vertexShaderFilePath, ShaderType::Vertex);
        Shader fragmentShader(fragmentShaderFilePath, ShaderType::Fragment);

        GLCall(m_RendererId = glCreateProgram());

        GLCall(glAttachShader(m_RendererId, vertexShader.GetShaderId()));
        GLCall(glAttachShader(m_RendererId, fragmentShader.GetShaderId()));

        GLCall(glLinkProgram(m_RendererId));
        GLCall(glValidateProgram(m_RendererId));
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_RendererId);
    }

    void ShaderProgram::Bind() const {
        GLCall(glUseProgram(m_RendererId));
    }

    void ShaderProgram::Unbind() const {
        GLCall(glUseProgram(0));
    }

    template<>
    void ShaderProgram::SetUniform(const std::string &name, float v0) {
        GLCall(glUniform1f(GetUniformLocation(name), v0));
    }
    template<>
    void ShaderProgram::SetUniform(const std::string &name, float v0, float v1) {
        GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
    }
    template<>
    void ShaderProgram::SetUniform(const std::string &name, float v0, float v1, float v2) {
        GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
    }
    template<>
    void ShaderProgram::SetUniform(const std::string &name, float v0, float v1, float v2, float v3) {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    template<>
    void ShaderProgram::SetUniform(const std::string &name, int v0) {
        GLCall(glUniform1i(GetUniformLocation(name), v0));
    }
    template<>
    void ShaderProgram::SetUniform(const std::string &name, int v0, int v1) {
        GLCall(glUniform2i(GetUniformLocation(name), v0, v1));
    }
    template<>
    void ShaderProgram::SetUniform(const std::string &name, int v0, int v1, int v2) {
        GLCall(glUniform3i(GetUniformLocation(name), v0, v1, v2));
    }
    template<>
    void ShaderProgram::SetUniform(const std::string &name, int v0, int v1, int v2, int v3) {
        GLCall(glUniform4i(GetUniformLocation(name), v0, v1, v2, v3));
    }

    int ShaderProgram::GetUniformLocation(const std::string &name) {
        if(m_UniformLocationCache.contains(name)) {
            return m_UniformLocationCache[name];
        }
        GLCall(int location = glGetUniformLocation(m_RendererId, name.c_str()));
        if(location == -1) {
            std::cout << "Warning: Uniform '" << name << "' wasn't found." << std::endl;
        }

        m_UniformLocationCache[name] = location;
        return location;
    }
} // OpenGLLearning