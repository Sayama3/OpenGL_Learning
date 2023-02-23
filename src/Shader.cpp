//
// Created by Sayama on 23/02/2023.
//

#include "Shader.hpp"
#include "Renderer.hpp"
#include "SystemHelper.hpp"
#include <iostream>

namespace Sayama::OpenGLLearning {

    Shader::Shader(const std::string& filePath, unsigned int type) : m_FilePath(filePath), m_ShaderType(type), m_RendererId(0) {
        CompileShader();
    }

    Shader::~Shader() {
        GLCall(glDeleteShader(m_RendererId));
    }

    bool Shader::CompileShader() {
        std::string source = SystemHelper::ReadFile(m_FilePath);

        GLCall(m_RendererId = glCreateShader(m_ShaderType));
        const char *src = source.c_str();
        GLCall(glShaderSource(m_RendererId, 1, &src, nullptr));
        GLCall(glCompileShader(m_RendererId));

        int result;
        GLCall(glGetShaderiv(m_RendererId, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE) {
            int length;
            GLCall(glGetShaderiv(m_RendererId, GL_INFO_LOG_LENGTH, &length));
            char *message = (char *) alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(m_RendererId, length, nullptr, message));
            std::cerr << "Failed to compile "
                      << (m_ShaderType == GL_VERTEX_SHADER ? "vertex" : (m_ShaderType == GL_FRAGMENT_SHADER ? "fragment" : "a"))
                      << " shader!" << std::endl;
            std::cerr << message << std::endl;
            GLCall(glDeleteShader(m_RendererId));
            return false;
        }

        return true;
    }

    unsigned int Shader::GetShaderId() const {
        return m_RendererId;
    }
} // OpenGLLearning