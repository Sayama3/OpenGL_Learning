//
// Created by Sayama on 21/02/2023.
//

#include <iostream>
#include <stdexcept>
#include "Renderer.hpp"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char *function, const char *file, int line) {
    bool dontHasError = true;
    while (GLenum error = glGetError() != GL_NO_ERROR) {
        dontHasError = false;
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
    }
    return dontHasError;
}

namespace Sayama::OpenGLLearning {

} // Sayama