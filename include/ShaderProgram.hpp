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

            void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        private:
            int GetUniformLocation(const std::string& name);
        };

    } // OpenGLLearning
