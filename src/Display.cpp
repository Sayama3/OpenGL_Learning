//
// Created by Sayama on 21/02/2023.
//

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include "ErrorHandling.hpp"
#include "Display.hpp"


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace Sayama::OpenGLLearning {
    Display::Display(const char *name, int width, int height, bool allowResize) :
    m_Window(nullptr),
    m_Name(name),
    m_Width(width),
    m_Height(height),
    glsl_version(nullptr),
    io(nullptr) {

        /* Initialize the library */
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            throw std::runtime_error("Couldn't initialize GLFW.");

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_RESIZABLE, allowResize ? GL_TRUE : GL_FALSE);
#elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
        glfwWindowHint(GLFW_RESIZABLE, allowResize ? GL_TRUE : GL_FALSE);
#else
        // GL 4.6 + GLSL 330
        glsl_version = "#version 330";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
        glfwWindowHint(GLFW_RESIZABLE, allowResize ? GL_TRUE : GL_FALSE);
#endif

        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, nullptr, nullptr);
        if (m_Window == nullptr) {
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

#ifdef __EMSCRIPTEN__
        EMSCRIPTEN_MAINLOOP_END;
#endif

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Display::ShouldClose() const {
        return glfwWindowShouldClose(this->m_Window);
    }

    GLFWwindow *Display::GetWindow() const {
        return this->m_Window;
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
        glfw_error_callback(0, "bonjour");
    }

    void Display::InitializeImGUI() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
        (void)&io;
        io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
        io->Fonts->AddFontDefault();
        //io->Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io->Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io->Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io->Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io->Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
    }

    void Display::BeginFrame() const {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }

    void Display::EndFrame() const {
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        /* Poll for and process events */
        glfwPollEvents();

        /* Swap front and back buffers */
        glfwSwapBuffers(this->GetWindow());
    }
} // OpenGLLearning


