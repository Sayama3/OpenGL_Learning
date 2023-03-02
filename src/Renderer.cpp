//
// Created by Sayama on 21/02/2023.
//

#include "Renderer.hpp"
#include "ErrorHandling.hpp"
#include "GL/glew.h"

namespace Sayama::OpenGLLearning {

    void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &shader) const {
        shader.Bind();

        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetType(), nullptr));
    }

    Renderer::Renderer() : m_RendererId(0) {

    }

    Renderer::~Renderer() {

    }

    void Renderer::Clear() const {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

} // Sayama