#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace TRL
{


class GpuObjectHandle
{
public:
    GpuObjectHandle()
        : m_Id(0)
    {
    }

    GpuObjectHandle(int id)
        : m_Id(id)
    {
    }

    int Id() const
    {
        return m_Id;
    }


private:
    int m_Id;
};

class GpuBufferHandle : public GpuObjectHandle
{
};

class GpuProgramHandle : public GpuObjectHandle
{
};

class GpuShaderHandle : public GpuObjectHandle
{
};

class GpuTextureHandle : public GpuObjectHandle
{
};

class GpuTexture2DHandle : public GpuTextureHandle
{
};

class GpuAttributeDataHandle : public GpuObjectHandle
{
};


} // end of namespace TRL