#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include "debug-trap.h"

#ifndef PSNIP_NDEBUG
#define ASSERT(x) if (!(x)) psnip_trap()
#else
#define ASSERT(x) (x)
#endif
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function = "", const char* file = __FILE__, int line = __LINE__)
{
    bool dontHasError = true;
    while (GLenum error = glGetError() != GL_NO_ERROR)
    {
        dontHasError = false;
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
    }
    return dontHasError;
}

static std::string ReadFile(const char* path) {
    std::ifstream fileStream(path);
    std::stringstream file;
    std::string line;
    while (std::getline(fileStream, line)) {
        file << line << "\n";
    }
    return file.str();
}

static std::optional<unsigned int> CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    //TODO: Error Handling.
    // Query the result :
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, nullptr, message));
        std::cerr << "Failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "a")) <<" shader!" << std::endl;
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
static std::optional<unsigned int> CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());

    std::optional<unsigned int> vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    std::optional<unsigned int> fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if(!vs.has_value() || !fs.has_value())
    {
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

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // Initialize GLEW NEED TO HAVE A VALID OPENGL CONTEXT TO INITIALIZE GLEW !!!
    auto glewErr = glewInit();
    if(glewErr != GLEW_OK) {
        std::cerr << "GLEW error (" << glewErr << "): " << glewGetErrorString(glewErr) << std::endl;
        return -1;
    }

    GLCall(std::cout << glGetString(GL_VERSION) << std::endl);

    const unsigned int NumberOfVertices = 4;
    const unsigned int NumberOfParameterPerVertices = 2;
    const unsigned int NumberOfIndex = 6;

    // Creating the vertices array
    float vertices[NumberOfVertices * NumberOfParameterPerVertices] = {
            -0.5f,-0.5f, //0
            0.5f,-0.5f, //1
            0.5f,0.5f, //2
            -0.5f,0.5f, //3
    };

    // it needs to be an unsigned int !
    unsigned int indexes[NumberOfIndex] = {
            0,1,2,
            2, 3, 0
    };

    // Creating the Vertex Array Object
    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    /* Create a verticesBufferId */

    // the id of the verticesBufferId.
    // In openGL, everything get attribute an ID, so, this is the ID of the verticesBufferId
    const unsigned int NumberOfBuffer = 2;
    unsigned int bufferIds[NumberOfBuffer];
    unsigned int& verticesBufferId = bufferIds[0];
    unsigned int& indexBufferId = bufferIds[1];

    // Asking for a verticesBufferId and giving the pointer to the verticesBufferId variable.
    GLCall(glGenBuffers(NumberOfBuffer, bufferIds));


    // Selecting (binding) the buffer for opengl to know we want to use it and how to use it.
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, verticesBufferId));

    // Say to OpenGL how large the buffer is (and whether we fill it)
    // The size is in bytes. Cf documentation (i.e. https://docs.gl)
    GLCall(glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * NumberOfParameterPerVertices * sizeof(float), vertices, GL_STATIC_DRAW));

    // Add the index buffer in CG
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumberOfIndex * sizeof(unsigned int), indexes, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    // Link the current buffer to the Vertex Arrays Object. (l176 or something)
    GLCall(glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, sizeof(float) * NumberOfParameterPerVertices, nullptr));

    std::string vertexShader = ReadFile("resources/shaders/shader.vert");
    std::string fragmentShader = ReadFile("resources/shaders/shader.frag");

    std::optional<unsigned int> program = CreateShader(vertexShader, fragmentShader);

    if(!program.has_value()) {
        glfwTerminate();
        return -1;
    }

    GLCall(glUseProgram(program.value()));

    GLCall(int colorUniformLocation = glGetUniformLocation(program.value(), "u_Color"));
    ASSERT(colorUniformLocation != -1);
    GLCall(glUniform4f(colorUniformLocation, 0.0, 1.0, 0.0, 1.0));

    float r = 0.0;
    float increment= 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));


        GLCall(glUniform4f(colorUniformLocation, r, 1.0, 0.0, 1.0));
        GLCall(glDrawElements(GL_TRIANGLES, NumberOfIndex, GL_UNSIGNED_INT, nullptr));

        if(r >= 1.0f) {
            increment = -0.01;
        } else if (r <= 0.0f) {
            increment = 0.01;
        }

        r += increment;

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }

    glDeleteProgram(program.value());
    glfwTerminate();
    return 0;
}
