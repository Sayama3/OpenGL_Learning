//
// Created by Sayama on 21/02/2023.
//

#include "Renderer.hpp"
#include "Display.hpp"
#include <stdexcept>
#include <iostream>

namespace Sayama {
    namespace OpenGLLearning {
        Display::Display(const char* name, int width, int height) : m_Name(name), m_Width(width), m_Height(height) {
            /* Initialize the library */
            if (!glfwInit()) {
                throw std::runtime_error("Couldn't initialize GLFW.");
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            /* Create a windowed mode window and its OpenGL context */
            m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, nullptr, nullptr);
            if (!m_Window)
            {
                glfwTerminate();
                throw std::runtime_error("Couldn't create the GLFW window.");
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(m_Window);

            glfwSwapInterval(1);

            // Initialize GLEW NEED TO HAVE A VALID OPENGL CONTEXT TO INITIALIZE GLEW !!!
            unsigned int glewErr = glewInit();
            if(glewErr != GLEW_OK) {
                const char * errorString = reinterpret_cast<const char *>(glewGetErrorString(glewErr));
                std::string errorMessage = "GLEW error (" + std::to_string(glewErr) + "): " + errorString;
                std::cerr << errorMessage << std::endl;
                throw std::runtime_error(errorMessage);
            }

            GLCall(std::cout << glGetString(GL_VERSION) << std::endl);

        }

        Display::~Display() {
            glfwTerminate();
        }

        bool Display::ShouldClose() const {
            return glfwWindowShouldClose(this->m_Window);
        }

        GLFWwindow* Display::GetWindow() const {
            return this->m_Window;
        }

        void Display::SwapBuffers() const {
            /* Swap front and back buffers */
            glfwSwapBuffers(this->GetWindow());
        }

        void Display::PollEvents() const {
            /* Poll for and process events */
            glfwPollEvents();
        }
    } // Sayama
} // OpenGLLearning