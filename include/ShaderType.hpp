//
// Created by Sayama on 23/02/2023.
//

#pragma once

#include "Renderer.hpp"

namespace Sayama::OpenGLLearning {
    enum ShaderType : unsigned int {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };
}