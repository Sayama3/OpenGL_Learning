//
// Created by Sayama on 23/02/2023.
//

#pragma once
#include <string>
#include <Shader.hpp>
#include <unordered_map>

namespace Sayama::OpenGLLearning {

    class ShaderProgram {
        private:
            unsigned int m_RendererId;
            std::unordered_map<std::string, int> m_UniformLocationCache;
        public:
            ShaderProgram(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
            ~ShaderProgram();

            void Bind() const;
            void Unbind() const;

            template<typename T>
            void SetUniform(const std::string& name, T v0);
            template<typename T>
            void SetUniform(const std::string& name, T v0, T v1);
            template<typename T>
            void SetUniform(const std::string& name, T v0, T v1, T v2);
            template<typename T>
            void SetUniform(const std::string& name, T v0, T v1, T v2, T v3);

        private:
            int GetUniformLocation(const std::string& name);
        };

    template<>
    void ShaderProgram::SetUniform(const std::string& name, float v0);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, float v0, float v1);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, float v0, float v1, float v2);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, float v0, float v1, float v2, float v3);

    template<>
    void ShaderProgram::SetUniform(const std::string& name, int v0);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, int v0, int v1);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, int v0, int v1, int v2);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, int v0, int v1, int v2, int v3);

    } // OpenGLLearning
