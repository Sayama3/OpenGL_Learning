#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
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

    float minDimension = glm::min(display.GetWidth(), display.GetHeight());
    glm::vec2 size = glm::vec2(minDimension * 0.5f);
    glm::vec2 halfSize = size * 0.5f;
    glm::vec2 center = glm::vec2 (display.GetWidth() * 0.5f, display.GetHeight() * 0.5f);
    float vertices[NumberOfVertices * NumberOfParameterPerVertices] = {
            center.x - halfSize.x, center.y - halfSize.y, 0.0f,0.0f, //0
            center.x + halfSize.x, center.y - halfSize.y, 1.0f,0.0f, //1
            center.x + halfSize.x, center.y + halfSize.y, 1.0f, 1.0f, //2
            center.x - halfSize.x, center.y + halfSize.y, 0.0f,1.0f,  //3
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



    Sayama::OpenGLLearning::ShaderProgram shaderProgram("resources/shaders/shader.vert", "resources/shaders/shader.frag");
    shaderProgram.Bind();

    shaderProgram.SetUniform<float>("u_Color", 1.0,1.0,1.0,1.0);

    Sayama::OpenGLLearning::Texture texture("resources/textures/perfect_kuzco.jpg");

    texture.Bind(0);
    shaderProgram.SetUniform("u_Texture", 0);

    vertexArray.Unbind();
    shaderProgram.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    Sayama::OpenGLLearning::Renderer renderer;
    display.InitializeImGUI();

    glm::vec4 color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
    static float alpha = 1.0f;

    glm::vec3 modelTranslation(50,50,0);
    glm::vec3 cameraTranslation(0,50,0);

    /* Loop until the user closes the window */
    while (!display.ShouldClose()) {
        /* Render here */
        renderer.Clear();
        display.BeginFrame();

        // TODO: To remove this, we have to create Materials (i.e. Shader + data)
        shaderProgram.Bind();

        // Projection Matrix to go from pixel to camera space.
        glm::mat4 proj = display.GetScreenMatrix();
        // View matrix to simulate camera position (i.e. moving camera 100 to the right means moving everything 100 to the left)
        glm::mat4 view = glm::translate(glm::mat4(1.0f), -cameraTranslation);
        // Model matrix that position (and later on rotate and scale) the object in the scene.
        glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslation);
        // Order important, might change depending on the graphical API. In OpenGL it's reverse from the acronym.
        // Link to the memory layout. In OpenGL it's in column major instead of row layout.
        glm::mat4 mvp = proj * view * model;

        shaderProgram.SetUniform("u_MVP", mvp);
        shaderProgram.SetUniform<float>("u_Color", color.x * alpha, color.y * alpha, color.z * alpha, color.w * alpha);

        renderer.Draw(vertexArray, indexBuffer, shaderProgram);

        // Our ImGUI Window
        {
            ImGui::Begin("Rendering Parameters");

            ImGui::SliderFloat("Alpha", &alpha, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color", (float*)&color);

            ImGui::NewLine();

            float maxDimension = glm::max(display.GetWidth(), display.GetHeight()) * 0.5f;
            ImGui::SliderFloat2("Camera Translation", &cameraTranslation.x, -maxDimension, maxDimension);
            ImGui::SliderFloat2("Picture Translation", &modelTranslation.x, -maxDimension, maxDimension);

            ImGui::NewLine();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        display.EndFrame();
    }

    return 0;
}
