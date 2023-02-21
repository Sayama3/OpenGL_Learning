//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include <vector>
#include <stdexcept>
#include "GL/glew.h"

namespace Sayama::OpenGLLearning {

    struct VertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        inline unsigned int GetSizeOfType() const { return GetSizeOfType(type); }

        static unsigned int GetSizeOfType(unsigned int type);
    };

    class VertexBufferLayout {
    private:
        unsigned int m_Stride;
        std::vector<VertexBufferElement> m_Elements;
    public:
        VertexBufferLayout();

        template<typename T>
        inline void Push(unsigned int count) {
            throw std::runtime_error("Type not implemented.");
        }

        inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }

        inline unsigned int GetStride() const { return m_Stride; }
    };

    template<>
    inline void VertexBufferLayout::Push<float>(unsigned int count) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template<>
    inline void VertexBufferLayout::Push<int>(unsigned int count) {
        m_Elements.push_back({GL_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_INT) * count;
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    template<>
    inline void VertexBufferLayout::Push<char>(unsigned int count) {
        m_Elements.push_back({GL_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_BYTE) * count;
    }
} // OpenGLLearning
