//
// Created by Sayama on 02/03/2023.
//
#include "ErrorHandling.hpp"
#include <iostream>
#include "GL/glew.h"


void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
    bool dontHasError = true;
    unsigned int error;
    while ( ( error = glGetError() ) != Sayama::OpenGLLearning::ErrorType::NoError) {
        dontHasError = false;
        std::cout << "[OpenGL Error] (" << error << ": "<< Sayama::OpenGLLearning::GetErrorName(error) <<"): " << function << " " << file << ":" << line << "\n"
                  << Sayama::OpenGLLearning::GetErrorDescription(error) << std::endl;
    }
    return dontHasError;
}
