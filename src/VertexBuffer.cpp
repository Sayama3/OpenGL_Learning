//
// Created by Sayama on 21/02/2023.
//

#include "VertexBuffer.hpp"
#include "Renderer.hpp"

namespace Sayama::OpenGLLearning {
    OpenGLLearning::VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
        GLCall(glGenBuffers(1, &this->m_RendererId));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererId));
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    VertexBuffer::~VertexBuffer() {
        GLCall(glDeleteBuffers(1, &this->m_RendererId));
    }

    void VertexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererId));
    }

    void VertexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
} // OpenGLLearning