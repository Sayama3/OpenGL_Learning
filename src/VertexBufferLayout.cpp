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
} // OpenGLLearning