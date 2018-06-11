#include "TRL/GpuTexture.h"


namespace TRL
{


void GpuTexture::Bind() const
{
    glBindTexture(m_Type, m_TextureInner);
}

void GpuTexture::ActiveTexture(int textureUnit) const
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    Bind();
}


} // end of namespace TRL