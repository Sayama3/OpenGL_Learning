//
// Created by Sayama on 21/02/2023.
//

#pragma once

namespace Sayama {
    namespace OpenGLLearning {

        class VertexBuffer {
        private:
            unsigned int m_RendererId;
        public:
            VertexBuffer(const void* data, unsigned int size);
            ~VertexBuffer();

            void Bind() const;
            void Unbind() const;
        };

    } // Sayama
} // OpenGLLearning
