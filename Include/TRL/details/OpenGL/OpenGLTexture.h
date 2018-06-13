#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/OpenGL/OpenGLCommonType.h"


namespace TRL
{

namespace details
{


class OpenGLTexture
{
public:
    void Bind() const
    {
        glBindTexture(m_NativeType, m_TextureInner);
    }

    void ActiveTextureUnit(int textureUnit) const
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        Bind();
    }

    GLuint GetInnerName() const { return m_TextureInner; }


protected:
    OpenGLTexture()
        :
        m_Type(GPU_TEXTURE_TYPE_INIT),
        m_TextureInner(-1),
        m_NativeType(0)
    {
    }


protected:
    GpuTextureType m_Type;
    GLuint m_NativeType;
    GLuint m_TextureInner;
};


} // end of namespace details

} // end of namespace TRL