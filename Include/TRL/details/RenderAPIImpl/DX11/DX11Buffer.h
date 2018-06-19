#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/RenderAPIImpl/DX11/DX11CommonType.h"


namespace TRL
{

namespace details
{


class DX11Buffer
{
public:
    DX11Buffer()
        :
        BufferType(GPU_BUFFER_TYPE_INIT),
        Access(GpuBufferAccessType::GpuRead),
        ModifyHint(GpuBufferModifyHint::Static),
        D3D11Buffer(nullptr),
        D3D11Usage(D3D11_USAGE::D3D11_USAGE_DEFAULT)
    {}


public:
    bool CanUpdateByCpu() const
    {
        return Access == GpuBufferAccessType::CpuWrite_GpuRead;
    }


public:
    GpuBufferType BufferType;
    GpuBufferAccessType Access;
    GpuBufferModifyHint ModifyHint;

    ID3D11Buffer* D3D11Buffer;
    D3D11_USAGE D3D11Usage;
};


} // end of namespace details

} // end of namespace TRL