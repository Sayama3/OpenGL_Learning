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


    // Projection Matrix to go from pixel to camera space.
    glm::mat4 proj = display.GetScreenMatrix();
    // View matrix to simulate camera position (i.e. moving camera 100 to the right means moving everything 100 to the left)
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100,0,0));
    // Model matrix that position (and later on rotate and scale) the object in the scene.
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(50,50,0));

    // Order important, might change depending on the graphical API. In OpenGL it's reverse from the acronym.
    // Link to the memory layout. In OpenGL it's in column major instead of row layout.
    glm::mat4 mvp = proj * view * model;

    Sayama::OpenGLLearning::ShaderProgram shaderProgram("resources/shaders/shader.vert", "resources/shaders/shader.frag");
    shaderProgram.Bind();
    shaderProgram.SetUniform("u_MVP", mvp);

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


    display.InitializeImGUI();

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    glm::vec4 color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
    static float alpha = 1.0f;

    /* Loop until the user closes the window */
    while (!display.ShouldClose()) {
        /* Render here */
        renderer.Clear();
        display.BeginFrame();

        // TODO: To remove this, we have to create Materials (i.e. Shader + data)
        shaderProgram.Bind();
        shaderProgram.SetUniform<float>("u_Color", color.x * alpha, color.y * alpha, color.z * alpha, color.w * alpha);

        renderer.Draw(vertexArray, indexBuffer, shaderProgram);

        if (r >= 1.0f) {
            increment = -0.01;
        } else if (r <= 0.0f) {
            increment = 0.01;
        }

        r += increment;
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("alpha", &alpha, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("color", (float*)&color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        display.EndFrame();
    }

    return 0;
}
