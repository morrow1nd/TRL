#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/Vector.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "TRL/CommonType.h"


namespace TRL
{


class AttributeVariable;
class UniformVariable;


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
    bool Init(const ToyUtility::String& rawSourceCode, GpuShaderType type);
    bool IsCompiledSucc() const;
    const ToyUtility::String& GetCompileLogInfo() const;
    GpuShaderType GetShaderType() const;
    void Destory();
    
    bool IsGeneratedByTRLShader() const;

    friend class GpuProgram;

private:
    struct ShaderInfo
    {
        ToyUtility::Vector<UniformVariable> Uniforms;
        ToyUtility::Vector<AttributeVariable> Attributes;
    };

private:
    bool m_CompiledSucc;
    GpuShaderInner m_ShaderInner;
    ToyUtility::String m_CompileLog;
    ToyUtility::SPtr<ShaderInfo> m_ShaderInfo;
};


} // end of namespace TRL