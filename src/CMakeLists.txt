cmake_minimum_required(VERSION 3.23)

add_subdirectory(vendor)

target_sources(OpenGL PRIVATE
        Application.cpp
        IndexBuffer.cpp
        Renderer.cpp
        VertexBuffer.cpp
        Display.cpp
        VertexArray.cpp
        VertexBufferLayout.cpp
        Shader.cpp
        ShaderProgram.cpp
        Texture.cpp
        )