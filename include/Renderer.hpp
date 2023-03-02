//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "ShaderProgram.hpp"

namespace Sayama::OpenGLLearning {
    class Renderer {
    private:
        unsigned int m_RendererId;
    public:
        Renderer();
        ~Renderer();

        void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
        void Clear() const;
    };

} // Sayama