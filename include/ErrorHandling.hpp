//
// Created by Sayama on 24/02/2023.
//

#ifndef OPENGL_LEARNING_ERRORHANDLING_HPP
#define OPENGL_LEARNING_ERRORHANDLING_HPP

#include <GL/glew.h>
#include <stdexcept>
#include "vendor/debug-trap.h"

#ifndef PSNIP_NDEBUG
#define ASSERT(x) if (!(x)) psnip_trap()
#else
#define ASSERT(x) if(!(x)) throw std::runtime_error(std::string(#x) + " is false.");
#endif

#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function = "", const char *file = __FILE__, int line = __LINE__);

namespace Sayama::OpenGLLearning {
    enum ErrorType {
        /// No error has been recorded. The value of this symbolic constant is guaranteed to be 0.
        NoError = GL_NO_ERROR,

        /// An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.
        InvalidEnum = GL_INVALID_ENUM,

        /// A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.
        InvalidValue = GL_INVALID_VALUE,

        /// The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.
        InvalidOperation = GL_INVALID_OPERATION,

        /// The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.
        InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,

        /// There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.
        OutOfMemory = GL_OUT_OF_MEMORY,

        /// An attempt has been made to perform an operation that would cause an internal stack to underflow.
        StackUnderflow = GL_STACK_UNDERFLOW,

        /// An attempt has been made to perform an operation that would cause an internal stack to overflow.
        StackOverflow = GL_STACK_OVERFLOW,
    };

    inline const char* GetErrorName(unsigned int errorNumber) {
        const char* errorName = nullptr;
        switch (errorNumber) {
            case ErrorType::NoError :
                errorName = "No Error";
                break;
            case ErrorType::InvalidEnum :
                errorName = "Invalid Enum";
                break;
            case ErrorType::InvalidValue :
                errorName = "Invalid Value";
                break;
            case ErrorType::InvalidOperation :
                errorName = "Invalid Operation";
                break;
            case ErrorType::InvalidFramebufferOperation :
                errorName = "Invalid Framebuffer Operation";
                break;
            case ErrorType::OutOfMemory :
                errorName = "Out Of Memory";
                break;
            case ErrorType::StackUnderflow :
                errorName = "Stack Underflow";
                break;
            case ErrorType::StackOverflow :
                errorName = "Stack Overflow";
                break;
            default:
                errorName = "Unknown Error";
                break;
        }
        return errorName;
    }

    inline const char* GetErrorDescription(unsigned int errorNumber) {
        const char* errorName = nullptr;
        switch (errorNumber) {
            case ErrorType::NoError :
                errorName = "No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
                break;
            case ErrorType::InvalidEnum :
                errorName = "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
                break;
            case ErrorType::InvalidValue :
                errorName = "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
                break;
            case ErrorType::InvalidOperation :
                errorName = "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
                break;
            case ErrorType::InvalidFramebufferOperation :
                errorName = "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.n";
                break;
            case ErrorType::OutOfMemory :
                errorName = "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
                break;
            case ErrorType::StackUnderflow :
                errorName = "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
                break;
            case ErrorType::StackOverflow :
                errorName = "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
                break;
            default:
                errorName = "Unknown error.";
                break;
        }
        return errorName;
    }
}
#endif //OPENGL_LEARNING_ERRORHANDLING_HPP
