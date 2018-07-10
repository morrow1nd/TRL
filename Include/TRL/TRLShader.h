#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/String/String.h"
#include "TRL/TRLCommonType.h"
//#include "TRL/TRLSL/TRLSLTokener.h"


namespace TRL
{

using namespace ToyUtility;
class GpuShader;


class TRLShader
{
public:
    bool Init(const String& code, GpuShaderType shaderType);

    const TRLSLTokenerError& GetTokenerError() const;

    SPtr<GpuShader> GenerateGpuShader(TRLNativeApiType targetType);


private:
    TRLSLTokener m_Tokener;
    GpuShaderType m_ShaderType;
};


} // end of namespace TRL