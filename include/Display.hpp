//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Sayama {
    namespace OpenGLLearning {

        class Display {
        private:
            GLFWwindow *m_Window;
            const char *m_Name;
            int m_Width;
            int m_Height;
            const char* glsl_version;
            ImGuiIO* io;
        public:
            Display(const char *name = "window", int width = 640, int height = 480);

            ~Display();

            bool ShouldClose() const;

            void InitializeImGUI();
            void BeginFrame() const;
            void EndFrame() const;

            GLFWwindow *GetWindow() const;

            glm::mat4 GetScreenMatrix() const;
            glm::mat4 GetScreenNormalizedMatrix() const;

            inline float GetWidth() const { return m_Width; }
            inline float GetHeight() const { return m_Height; }
            inline glm::vec2 GetSize() const { return glm::vec2(GetWidth(), GetHeight()); }

            inline float GetNormalizedWidth() const {
                return static_cast<float>(m_Width) / static_cast<float>(m_Height);
            }
            inline float GetNormalizedHeight() const {
                return 1.0f;
            }
            inline glm::vec2 GetNormalizedSize() const { return glm::vec2(GetNormalizedWidth(), GetNormalizedHeight()); }
        private:
            void OnWindowResize(int width, int height);
        };

    } // Sayama
} // OpenGLLearning
