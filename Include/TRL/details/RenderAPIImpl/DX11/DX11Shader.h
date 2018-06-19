#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/RenderAPIImpl/DX11/DX11CommonType.h"


namespace TRL
{

namespace details
{


struct DX11Shader
{
    DX11Shader()
        :
        Blob(nullptr),
        IsCompileSucc(false),
        CompileLogInfo()
    {
        D3DShaderPtr.VertexShader = nullptr;
    }


    GpuShaderType ShaderType;

    union
    {
        ID3D11VertexShader* VertexShader;
        ID3D11PixelShader* PixelShader;
    } D3DShaderPtr;

    ID3DBlob* Blob;

    bool IsCompileSucc;

    ToyUtility::String CompileLogInfo;
};


} // end of namespace details

} // end of namespace TRL