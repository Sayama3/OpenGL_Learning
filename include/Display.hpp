//
// Created by Sayama on 21/02/2023.
//

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Sayama {
    namespace OpenGLLearning {

        class Display {
        private:
            GLFWwindow *m_Window;
            const char *m_Name;
            int m_Width;
            int m_Height;
        public:
            Display(const char *name = "window", int width = 640, int height = 480);

            ~Display();

            bool ShouldClose() const;

            void SwapBuffers() const;

            void PollEvents() const;

            GLFWwindow *GetWindow() const;
        };

    } // Sayama
} // OpenGLLearning
