//
// Created by Sayama on 21/02/2023.
//

#include "IndexBuffer.hpp"
#include "ErrorHandling.hpp"

namespace Sayama::OpenGLLearning {
    OpenGLLearning::IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));

        GLCall(glGenBuffers(1, &this->m_RendererId));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererId));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }

    IndexBuffer::~IndexBuffer() {
        GLCall(glDeleteBuffers(1, &this->m_RendererId));
    }

    void IndexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererId));
    }

    void IndexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    unsigned int IndexBuffer::GetType() const {
        return GL_UNSIGNED_INT;
    }

    unsigned int IndexBuffer::GetCount() const {
        return m_Count;
    };
} // OpenGLLearning