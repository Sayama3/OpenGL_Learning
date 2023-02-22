//
// Created by Sayama on 21/02/2023.
//

#include "VertexBufferLayout.hpp"

namespace Sayama::OpenGLLearning {
    VertexBufferLayout::VertexBufferLayout() : m_Stride(0) {}

    unsigned int VertexBufferElement::GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
                return sizeof(GLfloat);
            case GL_UNSIGNED_INT:
                return sizeof(GLuint);
            case GL_INT:
                return sizeof(GLint);
            case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
            case GL_BYTE:
                return sizeof(GLbyte);
            default:
                throw std::runtime_error("Type not implemented.");
        }
    }

    template<>
    void VertexBufferLayout::Push<float>(unsigned int count) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }

    template<>
    void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template<>
    void VertexBufferLayout::Push<int>(unsigned int count) {
        m_Elements.push_back({GL_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_INT) * count;
    }

    template<>
    void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    template<>
    void VertexBufferLayout::Push<char>(unsigned int count) {
        m_Elements.push_back({GL_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_BYTE) * count;
    }
} // OpenGLLearning