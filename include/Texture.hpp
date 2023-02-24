//
// Created by Sayama on 24/02/2023.
//

#pragma once
#include <string>
#include <GL/glew.h>

namespace Sayama::OpenGLLearning {

    //TODO: Add documentation
    enum TextureTarget : unsigned int {
        Texture1D = GL_TEXTURE_1D,
        Texture2D = GL_TEXTURE_2D,
        Texture3D = GL_TEXTURE_3D,
        Texture1DArray = GL_TEXTURE_1D_ARRAY,
        Texture2DArray = GL_TEXTURE_2D_ARRAY,
        TextureRectangle = GL_TEXTURE_RECTANGLE,
        TextureCubeMap = GL_TEXTURE_CUBE_MAP,
        TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
        TextureBuffer = GL_TEXTURE_BUFFER,
        Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
        Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };

    //TODO: Add documentation
    enum TextureParameterName : unsigned int {
        DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
        BaseLevel = GL_TEXTURE_BASE_LEVEL,
        CompareFunc = GL_TEXTURE_COMPARE_FUNC,
        CompareMode = GL_TEXTURE_COMPARE_MODE,
        LodBias = GL_TEXTURE_LOD_BIAS,
        MinFilter = GL_TEXTURE_MIN_FILTER,
        MagFilter = GL_TEXTURE_MAG_FILTER,
        MinLod = GL_TEXTURE_MIN_LOD,
        MaxLod = GL_TEXTURE_MAX_LOD,
        MaxLevel = GL_TEXTURE_MAX_LEVEL,
        SwizzleR = GL_TEXTURE_SWIZZLE_R,
        SwizzleG = GL_TEXTURE_SWIZZLE_G,
        SwizzleB = GL_TEXTURE_SWIZZLE_B,
        SwizzleA = GL_TEXTURE_SWIZZLE_A,
        WrapS = GL_TEXTURE_WRAP_S,
        WrapT = GL_TEXTURE_WRAP_T,
        WrapR = GL_TEXTURE_WRAP_R,
    };

    // TODO: Add documentation
    enum TextureSlot : unsigned int {
        Texture0 = GL_TEXTURE0,
        Texture1 = GL_TEXTURE1,
        Texture2 = GL_TEXTURE2,
        Texture3 = GL_TEXTURE3,
        Texture4 = GL_TEXTURE4,
        Texture5 = GL_TEXTURE5,
        Texture6 = GL_TEXTURE6,
        Texture7 = GL_TEXTURE7,
        Texture8 = GL_TEXTURE8,
        Texture9 = GL_TEXTURE9,
        Texture10 = GL_TEXTURE10,
        Texture11 = GL_TEXTURE11,
        Texture12 = GL_TEXTURE12,
        Texture13 = GL_TEXTURE13,
        Texture14 = GL_TEXTURE14,
        Texture15 = GL_TEXTURE15,
        Texture16 = GL_TEXTURE16,
        Texture17 = GL_TEXTURE17,
        Texture18 = GL_TEXTURE18,
        Texture19 = GL_TEXTURE19,
        Texture20 = GL_TEXTURE20,
        Texture21 = GL_TEXTURE21,
        Texture22 = GL_TEXTURE22,
        Texture23 = GL_TEXTURE23,
        Texture24 = GL_TEXTURE24,
        Texture25 = GL_TEXTURE25,
        Texture26 = GL_TEXTURE26,
        Texture27 = GL_TEXTURE27,
        Texture28 = GL_TEXTURE28,
        Texture29 = GL_TEXTURE29,
        Texture30 = GL_TEXTURE30,
        Texture31 = GL_TEXTURE31,
        Count = 32,
    };

    class Texture {
    private:
        unsigned int m_RenderId;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;
    public:
        Texture(std::string path);
        ~Texture();

        void Bind(unsigned int slot = TextureSlot::Texture0) const;
        void Unbind() const;

        int GetWidth() const;
        int GetHeight() const;
        int GetBPP() const;
    };

} // OpenGLLearning
