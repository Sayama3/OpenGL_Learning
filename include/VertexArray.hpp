//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace Sayama::OpenGLLearning {
    class VertexArray {
    private:
        unsigned int m_RendererId;
    public:
        VertexArray();

        ~VertexArray();

        void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
        void Bind() const;
        void Unbind() const;
    };
} // OpenGLLearning
