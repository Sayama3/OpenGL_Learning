//
// Created by Sayama on 21/02/2023.
//

#pragma once

namespace Sayama::OpenGLLearning {

        class IndexBuffer {
        private:
            unsigned int m_RendererId;
            unsigned int m_Count;
        public:
            IndexBuffer(const unsigned int *data, unsigned int count);

            ~IndexBuffer();

            void Bind() const;

            void Unbind() const;

            unsigned int GetType() const;
            unsigned int GetCount() const;
        };

    } // OpenGLLearning
