//
// Created by Sayama on 21/02/2023.
//

#include "VertexArray.hpp"
#include "Renderer.hpp"

namespace Sayama::OpenGLLearning {
    VertexArray::VertexArray() {
        GLCall(glGenVertexArrays(1, &m_RendererId));
        GLCall(glBindVertexArray(m_RendererId));
    }

    VertexArray::~VertexArray() {
        GLCall(glDeleteVertexArrays(1, &m_RendererId));
    }

    void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
        Bind();
        vb.Bind();

        const auto &elements = layout.GetElements();
        unsigned int offset = 0;
        for (int i = 0; i < elements.size(); ++i) {
            const auto &element = elements[i];
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *) offset));
            offset += element.count * element.GetSizeOfType();
        }

    }

    void VertexArray::Bind() const {
        GLCall(glBindVertexArray(m_RendererId));
    }

    void VertexArray::Unbind() const {
        GLCall(glBindVertexArray(0));
    }

} // OpenGLLearning