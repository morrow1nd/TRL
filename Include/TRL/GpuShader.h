#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuShader
{
public:
    GpuShader()
        :
        m_CompiledSucc(false),
        m_ShaderInner(0)
    { }


public:
    //void Load(void* p, int size);
    bool Init(const ToyUtility::String& sourceCode, GpuShaderType type);
    bool IsCompiledSucc() const;
    const ToyUtility::String& GetCompileLogInfo() const;
    GpuShaderType GetShaderType() const;
    void Destory();
    
    friend class GpuProgram;

private:
    bool m_CompiledSucc;
    GpuShaderInner m_ShaderInner;
    ToyUtility::String m_CompileLog;
};


} // end of namespace TRL