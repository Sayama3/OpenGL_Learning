//
// Created by Sayama on 21/02/2023.
//

#include "Renderer.hpp"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
    bool dontHasError = true;
    while (GLenum error = glGetError() != GL_NO_ERROR) {
        dontHasError = false;
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
    }
    return dontHasError;
}

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