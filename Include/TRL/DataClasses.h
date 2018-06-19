#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "TRL/TRLCommonType.h"


namespace TRL
{


struct BYTE_DATA_DESC
{
    const void*                     SysMem;
    ToyUtility::uint32              Size; // (in bytes)
};

struct GPU_BUFFER_DESC
{
    GpuBufferType                   BufferType;
    GpuBufferAccessType             Access;
    GpuBufferModifyHint             ModifyHint;
    BYTE_DATA_DESC                  InitData;
};

struct GPU_SHADER_DESC
{
    ToyUtility::String              SourceCode;
    GpuShaderType                   ShaderType;
    bool                            DebugMode;
};


} // end of namespace TRL