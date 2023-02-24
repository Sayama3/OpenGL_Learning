//
// Created by Sayama on 23/02/2023.
//

#pragma once
#include <string>
#include <optional>
#include <GL/glew.h>

namespace Sayama::OpenGLLearning {
    enum ShaderType : unsigned int {
        Compute = GL_COMPUTE_SHADER,
        Vertex = GL_VERTEX_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEvaluation = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };

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
