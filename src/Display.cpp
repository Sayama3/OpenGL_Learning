//
// Created by Sayama on 21/02/2023.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include "ErrorHandling.hpp"
#include "Display.hpp"
#include "GL/glew.h"

namespace Sayama::OpenGLLearning {
    Display::Display(const char *name, int width, int height) : m_Name(name), m_Width(width), m_Height(height) {
        /* Initialize the library */
        if (!glfwInit()) {
            throw std::runtime_error("Couldn't initialize GLFW.");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            throw std::runtime_error("Couldn't create the GLFW window.");
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(1);

        // Initialize GLEW NEED TO HAVE A VALID OPENGL CONTEXT TO INITIALIZE GLEW !!!
        unsigned int glewErr = glewInit();
        if (glewErr != GLEW_OK) {
            const char *errorString = reinterpret_cast<const char *>(glewGetErrorString(glewErr));
            std::string errorMessage = "GLEW error (" + std::to_string(glewErr) + "): " + errorString;
            std::cerr << errorMessage << std::endl;
            throw std::runtime_error(errorMessage);
        }

        GLCall(std::cout << glGetString(GL_VERSION) << std::endl);

        // The Blending :
        // Not mandatory to enable first, but a lot nicer.
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        glfwSetWindowUserPointer(this->m_Window, this);

        auto func = [](GLFWwindow* window, int width, int height)
        {
            static_cast<Display*>(glfwGetWindowUserPointer(window))->OnWindowResize(width, height);
        };

        glfwSetWindowSizeCallback(m_Window, func);
    }

    Display::~Display() {
        glfwTerminate();
    }

    bool Display::ShouldClose() const {
        return glfwWindowShouldClose(this->m_Window);
    }

    GLFWwindow *Display::GetWindow() const {
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

    glm::mat4 Display::GetScreenMatrix() const {
        return glm::ortho(0.0f, static_cast<float>(this->m_Width), 0.0f, static_cast<float>(this->m_Height), 0.0f, 1.0f);
    }

    glm::mat4 Display::GetScreenNormalizedMatrix() const {
        return glm::ortho(0.0f, GetNormalizedWidth(), 0.0f,GetNormalizedHeight(), 0.0f,1.0f);
    }

    void Display::OnWindowResize(int width, int height) {
        m_Width = width;
        m_Height = height;
    }
} // OpenGLLearning