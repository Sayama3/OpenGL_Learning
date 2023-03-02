#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "Display.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main() {
    Sayama::OpenGLLearning::Display display;

    const unsigned int NumberOfVertices = 4;
    const unsigned int NumberOfParameterPerVertices = 2 + 2;

    float width = display.GetNormalizedWidth();
    // Creating the vertices array
    float offset = (width - 1.0f) / 2.0f;
    float vertices[NumberOfVertices * NumberOfParameterPerVertices] = {
            offset, 0.0f, 0.0f,0.0f, //0
            1.0f+offset, 0.0f, 1.0f,0.0f, //1
            1.0f+offset, 1.0f, 1.0f,1.0f, //2
            offset, 1.0f, 0.0f,1.0f,  //3
    };

    const unsigned int NumberOfIndex = 6;
    // it needs to be an unsigned int !
    unsigned int indices[NumberOfIndex] = {
            0, 1, 2,
            2, 3, 0
    };

    Sayama::OpenGLLearning::VertexArray vertexArray;
    Sayama::OpenGLLearning::VertexBuffer vertexBuffer(vertices,NumberOfVertices * NumberOfParameterPerVertices * sizeof(float));
    Sayama::OpenGLLearning::VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, layout);


    Sayama::OpenGLLearning::IndexBuffer indexBuffer(indices, NumberOfIndex);

    // Creating the 4 by 3 aspect ratio projection matrix.
//    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 proj = display.GetScreenNormalizedMatrix();

    Sayama::OpenGLLearning::ShaderProgram shaderProgram("resources/shaders/shader.vert", "resources/shaders/shader.frag");
    shaderProgram.Bind();
    shaderProgram.SetUniform("u_MVP", proj);

    shaderProgram.SetUniform<float>("u_Color", 1.0,1.0,1.0,1.0);

    Sayama::OpenGLLearning::Texture texture("resources/textures/perfect_kuzco.jpg");

    texture.Bind(0);
    shaderProgram.SetUniform("u_Texture", 0);

    vertexArray.Unbind();
    shaderProgram.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    float r = 0.0;
    float increment = 0.05f;

    Sayama::OpenGLLearning::Renderer renderer;

    /* Loop until the user closes the window */
    while (!display.ShouldClose()) {
        /* Render here */
        renderer.Clear();

        // TODO: To remove this, we have to create Materials (i.e. Shader + data)
        shaderProgram.Bind();
        shaderProgram.SetUniform<float>("u_Color", r, 1.0, 1.0, 1.0);

        renderer.Draw(vertexArray, indexBuffer, shaderProgram);

        if (r >= 1.0f) {
            increment = -0.01;
        } else if (r <= 0.0f) {
            increment = 0.01;
        }

        r += increment;

        display.SwapBuffers();
        display.PollEvents();
    }

    return 0;
}
