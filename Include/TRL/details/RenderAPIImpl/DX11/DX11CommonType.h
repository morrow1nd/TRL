#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include "ToyUtility/Prerequisites/PreDefine.h"


namespace TRL
{

namespace details
{


struct DX11ToNative
{
    static UINT Convert(GpuBufferType value)
    {
#if TRL_MORE_RUNTIME_CHECK
        switch (value)
        {
        case GpuBufferType::GPU_INDEX_BUFFER:
            return D3D11_BIND_INDEX_BUFFER;
        case GpuBufferType::GPU_VERTEX_BUFFER:
            return D3D11_BIND_VERTEX_BUFFER;

        case GpuBufferType::GPU_BUFFER_TYPE_INIT:
            return 0;
        default:
            assert(false);
        }
        return 0;
#else
        // TODOM: using a array to convert
#endif
    }
};


} // end of namespace details

} // end of namespace TRL