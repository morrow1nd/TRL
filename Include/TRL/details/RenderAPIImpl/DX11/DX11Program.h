#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/RenderAPIImpl/DX11/DX11CommonType.h"
#include "TRL/GpuObjectHandles.h"


namespace TRL
{

namespace details
{


struct DX11Program
{
    DX11Program()
        :
        VertexShader(GpuObjectHandle::EmptyId),
        FragShader(GpuObjectHandle::EmptyId)
    {}


    GpuShaderHandle VertexShader;
    GpuShaderHandle FragShader;
};


} // end of namespace details

} // end of namespace TRL