//
// Created by Sayama on 23/02/2023.
//

#pragma once
#include <string>
#include <optional>
#include "ShaderType.hpp"

namespace Sayama::OpenGLLearning {
    class Shader {
    private:
        std::string m_FilePath;
        unsigned int m_ShaderType;
        unsigned int m_RendererId;
    public:
        Shader(const std::string& filePath, unsigned int type);
        ~Shader();

        unsigned int GetShaderId() const;

    private:
        bool CompileShader();
    };

} // OpenGLLearning
