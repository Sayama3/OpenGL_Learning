//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <optional>
#include <stdexcept>
#include "vendor/debug-trap.h"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "ShaderProgram.hpp"

#ifndef PSNIP_NDEBUG
#define ASSERT(x) if (!(x)) psnip_trap()
#else
#define ASSERT(x) if(!(x)) throw std::runtime_error(std::string(#x) + " is false.");
#endif

#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function = "", const char *file = __FILE__, int line = __LINE__);

namespace Sayama::OpenGLLearning {
    class Renderer {
    private:
        unsigned int m_RendererId;
    public:
        Renderer();
        ~Renderer();

        void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
        void Clear() const;
    };

} // Sayama