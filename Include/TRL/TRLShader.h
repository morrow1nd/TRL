#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/String/String.h"
#include "TRL/CommonType.h"


namespace TRL
{

using namespace ToyUtility;
class GpuShader;


class TRLShader
{
public:
    void Init(GpuShaderType shaderType);
    void LoadText(const String& trlShaderCode);
    SPtr<GpuShader> GenerateGpuShader(ToyRenderType targetType);
};


} // end of namespace TRL