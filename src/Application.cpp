#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

    glfwTerminate();
    return 0;
}
