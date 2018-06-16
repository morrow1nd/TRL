#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLCommonType.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLTexture.h"


namespace TRL
{

namespace details
{


class OpenGLTexture2D : public OpenGLTexture
{
public:
    void Init()
    {
        // TODO: maybe we could remove GpuTexture's m_Type, and use a virtual GetTextureType() function.
        m_Type = GpuTextureType::GPU_TEXTURE_2D;
        m_NativeType = TRL_GL_NATIVE(m_Type);
        glGenTextures(1, &m_TextureInner);
        glBindTexture(m_NativeType, m_TextureInner);
    }

    // level: specifies which mip level to load. The first level is specified by 0
    void UploadImage(GpuTextureBaseFormat internalFormat, uint32 width, uint32 height,
        PixelFormat format, PixelDataType type, const void* data, int level = 0)
    {
        glTexImage2D(m_NativeType, level, TRL_GL_NATIVE(internalFormat), width, height, 0,
            TRL_GL_NATIVE(format), TRL_GL_NATIVE(type), data);
        // http://docs.gl/es3/glTexImage2D
    }

    void SetMinFilter(GpuTextureMinFilterMode filterMode)
    {
        glTexParameteri(m_NativeType, GL_TEXTURE_MIN_FILTER, TRL_GL_NATIVE(filterMode));
    }
    void SetMagFilter(GpuTextureMagFilterMode filterMode)
    {
        glTexParameteri(m_NativeType, GL_TEXTURE_MAG_FILTER, TRL_GL_NATIVE(filterMode));
    }

    void SetWrapS(GpuTextureWrapMode wrapMode)
    {
        glTexParameteri(m_NativeType, GL_TEXTURE_WRAP_S, TRL_GL_NATIVE(wrapMode));
    }
    void SetWrapR(GpuTextureWrapMode wrapMode)
    {
        glTexParameteri(m_NativeType, GL_TEXTURE_WRAP_R, TRL_GL_NATIVE(wrapMode));
    }
    void SetWrapT(GpuTextureWrapMode wrapMode)
    {
        glTexParameteri(m_NativeType, GL_TEXTURE_WRAP_T, TRL_GL_NATIVE(wrapMode));
    }

    // Specifies the index of the lowest defined mipmap level. The initial value is 0.
    void SetBaseLevel(int level)
    {
        glTexParameteri(m_NativeType, GL_TEXTURE_BASE_LEVEL, level);
    }

    // more: compare_func, compare_mode, min_filter, max_filter, min_lod, max_lod, max_level, swizzle_(rgba)

    // Automatic generate mipmap
    void GenerateMipmap()
    {
        glGenerateMipmap(m_NativeType);
    }

    void Destory()
    {
        glDeleteTextures(1, &m_TextureInner);
    }
};


} // end of namespace details

} // end of namespace TRL