#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/Vector.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "TRL/CommonType.h"
#include "TRL/AttributeVariable.h"
#include "TRL/UniformVariable.h"


namespace TRL
{


class GpuShader;


class GpuProgram
{
public:
    bool Init(GpuShader& vertShader, GpuShader& fragShader);
    const ToyUtility::Vector<UniformVariable>& GetUniforms() const;
    const ToyUtility::Vector<AttributeVariable>& GetAttributes() const;
    const UniformVariable& FindUniform(const ToyUtility::String& name) const;
    const AttributeVariable& FindAttribute(const ToyUtility::String& name) const;
    void Destory();
    

    friend class RenderAPI;

public:
    struct AttributeUniformInfo
    {
        ToyUtility::Vector<UniformVariable> Uniforms;
        ToyUtility::Vector<AttributeVariable> Attributes;
    };


private:
    void _PrepareUniformInfos(GpuShader& vertShader, GpuShader& fragShader);
    void _PrepareAttributeInfos(GpuShader& vertShader, GpuShader& fragShader);

private:
    bool m_LinkedSucc;
    GpuProgramInner m_ProgramInner;
    ToyUtility::String m_LinkLog;
    AttributeUniformInfo m_VertShaderInfo;
    AttributeUniformInfo m_FragShaderInfo;
};


} // end of namespace TRL