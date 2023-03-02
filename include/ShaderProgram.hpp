//
// Created by Sayama on 23/02/2023.
//

#pragma once
#include <string>
#include <Shader.hpp>
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
            void SetUniform(const std::string& name, const T& v0);
            template<typename T>
            void SetUniform(const std::string& name, const T& v0, const T& v1);
            template<typename T>
            void SetUniform(const std::string& name, const T& v0, const T& v1, const T& v2);
            template<typename T>
            void SetUniform(const std::string& name, const T& v0, const T& v1, const T& v2, const T& v3);

        private:
            int GetUniformLocation(const std::string& name);
        };

    template<>
    void ShaderProgram::SetUniform(const std::string& name, const float& v0);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, const float& v0, const float& v1);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, const float& v0, const float& v1, const float& v2);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, const float& v0, const float& v1, const float& v2, const float& v3);

    template<>
    void ShaderProgram::SetUniform(const std::string& name, const int& v0);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, const int& v0, const int& v1);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, const int& v0, const int& v1, const int& v2);
    template<>
    void ShaderProgram::SetUniform(const std::string& name, const int& v0, const int& v1, const int& v2, const int& v3);

    template<>
    void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& v0);
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::vec1 & v0) {
        this->SetUniform<float>(name, v0[0]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::vec2 & v0) {
        this->SetUniform<float>(name, v0[0], v0[1]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::vec3 & v0) {
        this->SetUniform<float>(name, v0[0], v0[1], v0[2]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::vec4 & v0) {
        this->SetUniform<float>(name, v0[0], v0[1], v0[2], v0[3]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::ivec1 & v0) {
        this->SetUniform<int>(name, v0[0]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::ivec2 & v0) {
        this->SetUniform<int>(name, v0[0], v0[1]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::ivec3 & v0) {
        this->SetUniform<int>(name, v0[0], v0[1], v0[2]);
    }
    template<>
    inline void ShaderProgram::SetUniform(const std::string& name, const glm::ivec4 & v0) {
        this->SetUniform<int>(name, v0[0], v0[1], v0[2], v0[3]);
    }

    } // OpenGLLearning
