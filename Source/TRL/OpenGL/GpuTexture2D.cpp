#include "TRL/GpuTexture2D.h"


namespace TRL
{


void GpuTexture2D::Init()
{
    // TODO: maybe we could remove GpuTexture's m_Type, and use a virtual GetTextureType() function.
    m_Type = GpuTextureType::GPU_TEXTURE_2D;
    glGenTextures(1, &m_TextureInner);
    glBindTexture(m_Type, m_TextureInner);
}

void GpuTexture2D::UploadImage(GpuTextureBaseFormat internalFormat, GpuSizei width, GpuSizei height,
    PixelFormat format, PixelDataType type, const void * data, int level)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexImage2D(m_Type, level, internalFormat, width, height, 0, (GLenum)format, (GLenum)type, data);
    // http://docs.gl/es3/glTexImage2D
}

void GpuTexture2D::SetMinFilter(GpuTextureMinFilterMode filterMode)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER, (GLenum)filterMode);
}

void GpuTexture2D::SetMagFilter(GpuTextureMagFilterMode filterMode)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER, (GLenum)filterMode);
}

void GpuTexture2D::SetWrapS(GpuTextureWrapMode wrapMode)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_S, wrapMode);
}

void GpuTexture2D::SetWrapR(GpuTextureWrapMode wrapMode)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_R, wrapMode);
}

void GpuTexture2D::SetWrapT(GpuTextureWrapMode wrapMode)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_T, wrapMode);
}

void GpuTexture2D::SetBaseLevel(int level)
{
    glBindTexture(m_Type, m_TextureInner);
    glTexParameteri(m_Type, GL_TEXTURE_BASE_LEVEL, level);
}

void GpuTexture2D::GenerateMipmap()
{
    glBindTexture(m_Type, m_TextureInner);
    glGenerateMipmap(m_Type);
}

void GpuTexture2D::Destory()
{
    glDeleteTextures(1, &m_TextureInner);
}


} // end of namespace TRL