//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <optional>
#include <stdexcept>
#include "debug-trap.h"

#ifndef PSNIP_NDEBUG
#define ASSERT(x) if (!(x)) psnip_trap()
#else
#define ASSERT(x) if(!(x)) throw std::runtime_error(std::string(#x) + " is false.");
#endif
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function = "", const char *file = __FILE__, int line = __LINE__);

namespace Sayama {
    namespace OpenGLLearning {

        class Renderer {
        };

    } // OpenGLLearning
} // Sayama