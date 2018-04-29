#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuTexture
{
public:
    void Bind() const;

    void ActiveTexture(int textureUnit) const;


protected:
    GpuTexture()
        :
        m_Type(GPU_TEXTURE_TYPE_INIT),
        m_TextureInner(0)
    {}


protected:
    GpuTextureType m_Type;
    GpuTextureInner m_TextureInner;
};


} // end of namespace TRL