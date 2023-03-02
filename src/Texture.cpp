//
// Created by Sayama on 24/02/2023.
//

#include <iostream>
#include "ErrorHandling.hpp"
#include "GL/glew.h"
#include "Texture.hpp"
#include "vendor/stb/stb_image.h"

namespace Sayama::OpenGLLearning {
        Texture::Texture(std::string path)
                : m_RenderId(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(-1) , m_Height(-1) , m_BPP(-1)
        {
            // OpenGL is waiting for the texture to be at the bottom left, so inverting the texture in Y.
            stbi_set_flip_vertically_on_load(1);
            // Set 4 as in RGBA
            m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
            if (!m_LocalBuffer)
            {
               std::cout << "\nError: Failed to load texture" << std::endl;
               std::cout << stbi_failure_reason() << std::endl;
                ASSERT(m_LocalBuffer);
            }
            GLCall(glGenTextures(1, &m_RenderId));

            // Not using bind because I don't care about texture slot, just want to set the texture
            GLCall(glBindTexture(TextureTarget::Texture2D, m_RenderId));
            // Need this 4 parameters for not having a black texture.
            GLCall(glTexParameteri(TextureTarget::Texture2D, TextureParameterName::MinFilter, GL_LINEAR));
            GLCall(glTexParameteri(TextureTarget::Texture2D, TextureParameterName::MagFilter, GL_LINEAR));
            GLCall(glTexParameteri(TextureTarget::Texture2D, TextureParameterName::WrapS, GL_CLAMP_TO_EDGE));
            GLCall(glTexParameteri(TextureTarget::Texture2D, TextureParameterName::WrapT, GL_CLAMP_TO_EDGE));

            // We can pass nothing, in this case, it will just allocate for later on.
            GLCall(glTexImage2D(TextureTarget::Texture2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

            Unbind();

            if(m_LocalBuffer) {
                stbi_image_free(m_LocalBuffer);
            }
        }

        Texture::~Texture() {
            GLCall(glDeleteTextures(1, &m_RenderId));
        }

        void Texture::Bind(unsigned int slot) const {
            GLCall(glActiveTexture(GL_TEXTURE0 + slot));
            GLCall(glBindTexture(TextureTarget::Texture2D, m_RenderId));
        }

        void Texture::Unbind() const {
            GLCall(glBindTexture(TextureTarget::Texture2D, 0));
        }

        int Texture::GetWidth() const {
            return m_Width;
        }

        int Texture::GetHeight() const {
            return m_Height;
        }

        int Texture::GetBPP() const {
            return m_BPP;
        }
    } // OpenGLLearning