#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>

static std::string ReadFile(std::string path) {
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
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error Handling.
    // Query the result :
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, nullptr, message);
        std::cerr << "Failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "a")) <<" shader!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id);
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
    unsigned int program = glCreateProgram();

    std::optional<unsigned int> vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    std::optional<unsigned int> fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if(!vs.has_value() || !fs.has_value())
    {
        return {};
    }

    glAttachShader(program, vs.value());
    glAttachShader(program, fs.value());

    glLinkProgram(program);
    glValidateProgram(program);

    // Delete the shader as we now have created the program.
    glDeleteShader(vs.value());
    glDeleteShader(fs.value());

    return program;
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialize GLEW NEED TO HAVE A VALID OPENGL CONTEXT TO INITIALIZE GLEW !!!
    auto glewErr = glewInit();
    if(glewErr != GLEW_OK) {
        std::cerr << "GLEW error (" << glewErr << "): " << glewGetErrorString(glewErr) << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Creating the vertices array
    float position[6] = {
            -0.5f,-0.5f,
            0.0f,0.5f,
            0.5f,-0.5f
    };

    /* Create a bufferId */

    // the id of the bufferId.
    // In openGL, everything get attribute an ID, so, this is the ID of the bufferId
    unsigned int bufferId;

    // Asking for a bufferId and giving the pointer to the bufferId variable.
    glGenBuffers(1, &bufferId);

    // Selecting (binding) the buffer for opengl to know we want to use it and how to use it.
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);

    // Say to OpenGL how large the buffer is (and whether we fill it)
    // The size is in bytes. Cf documentation (i.e. https://docs.gl)
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    std::string vertexShader = ReadFile("resources/shaders/shader.vert");
    std::string fragmentShader = ReadFile("resources/shaders/shader.frag");

    std::optional<unsigned int> program = CreateShader(vertexShader, fragmentShader);

    if(!program.has_value()) {
        glfwTerminate();
        return -1;
    }

    glUseProgram(program.value());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw without an index buffer.
        // Here it's 3 vertices as a vertices is 2 float. (and we set 6 floats so 3 vertices)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // The sames things but with index buffer !
        // glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, [...]);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(program.value());
    glfwTerminate();
    return 0;
}
