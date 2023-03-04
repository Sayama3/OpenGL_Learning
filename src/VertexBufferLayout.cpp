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

    template<>
    void VertexBufferLayout::Push<glm::vec2>(unsigned int count) {
        Push<float>(count * 2); // vec2 = 2 float.
    }
    template<>
    void VertexBufferLayout::Push<glm::vec3>(unsigned int count) {
        Push<float>(count * 3); // vec3 = 3 float.
    }
    template<>
    void VertexBufferLayout::Push<glm::vec4>(unsigned int count) {
        Push<float>(count * 4); // vec4 = 4 float.
    }

    template<>
    void VertexBufferLayout::Push<glm::ivec2>(unsigned int count) {
        Push<int>(count * 2); // ivec2 = 2 int.
    }
    template<>
    void VertexBufferLayout::Push<glm::ivec3>(unsigned int count) {
        Push<int>(count * 3); // ivec3 = 3 int.
    }
    template<>
    void VertexBufferLayout::Push<glm::ivec4>(unsigned int count) {
        Push<int>(count * 4); // ivec4 = 4 int.
    }
} // OpenGLLearning