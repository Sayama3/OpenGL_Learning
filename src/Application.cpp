#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "Display.hpp"
#include "VertexArray.hpp"

static std::string ReadFile(const char *path) {
    std::ifstream fileStream(path);
    std::stringstream file;
    std::string line;
    while (std::getline(fileStream, line)) {
        file << line << "\n";
    }
    return file.str();
}

static std::optional<unsigned int> CompileShader(unsigned int type, const std::string &source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    //TODO: Error Handling.
    // Query the result :
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, nullptr, message));
        std::cerr << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "a"))
                  << " shader!" << std::endl;
        std::cerr << message << std::endl;
        GLCall(glDeleteShader(id));
        return {};
    }

    return id;
}

/// Create a shader from source code.
/// \param vertexShader the source code of the vertex shader.
/// \param fragmentShader the source code of the fragment shader.
/// \return The id of the shader in OpenGL.
static std::optional<unsigned int>
CreateShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());

    std::optional<unsigned int> vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    std::optional<unsigned int> fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if (!vs.has_value() || !fs.has_value()) {
        return {};
    }

    GLCall(glAttachShader(program, vs.value()));
    GLCall(glAttachShader(program, fs.value()));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // Delete the shader as we now have created the program.
    GLCall(glDeleteShader(vs.value()));
    GLCall(glDeleteShader(fs.value()));

    return program;
}

int main() {
    Sayama::OpenGLLearning::Display display;

    const unsigned int NumberOfVertices = 4;
    const unsigned int NumberOfParameterPerVertices = 2;

    // Creating the vertices array
    float vertices[NumberOfVertices * NumberOfParameterPerVertices] = {
            -0.5f, -0.5f, //0
            0.5f, -0.5f, //1
            0.5f, 0.5f, //2
            -0.5f, 0.5f, //3
    };

    Sayama::OpenGLLearning::VertexArray va;
    Sayama::OpenGLLearning::VertexBuffer vertexBuffer(vertices,NumberOfVertices * NumberOfParameterPerVertices * sizeof(float));
    Sayama::OpenGLLearning::VertexBufferLayout vbl;
    vbl.Push<float>(2);
    va.AddBuffer(vertexBuffer, vbl);

    const unsigned int NumberOfIndex = 6;

    // it needs to be an unsigned int !
    unsigned int indices[NumberOfIndex] = {
            0, 1, 2,
            2, 3, 0
    };

    Sayama::OpenGLLearning::IndexBuffer indexBuffer(indices, NumberOfIndex);

    std::string vertexShader = ReadFile("resources/shaders/shader.vert");
    std::string fragmentShader = ReadFile("resources/shaders/shader.frag");
    std::optional<unsigned int> program = CreateShaderProgram(vertexShader, fragmentShader);

    if (!program.has_value()) {
        glfwTerminate();
        return -1;
    }

    GLCall(glUseProgram(program.value()));

    GLCall(int colorUniformLocation = glGetUniformLocation(program.value(), "u_Color"));
    ASSERT(colorUniformLocation != -1);
    GLCall(glUniform4f(colorUniformLocation, 0.0, 1.0, 0.0, 1.0));

    float r = 0.0;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!display.ShouldClose()) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUseProgram(program.value()));
        GLCall(glUniform4f(colorUniformLocation, r, 1.0, 0.0, 1.0));

        va.Bind();
        indexBuffer.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), indexBuffer.GetType(), nullptr));

        if (r >= 1.0f) {
            increment = -0.01;
        } else if (r <= 0.0f) {
            increment = 0.01;
        }

        r += increment;

        display.SwapBuffers();
        display.PollEvents();
    }

    glDeleteProgram(program.value());

    return 0;
}
