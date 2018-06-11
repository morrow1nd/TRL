#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "TRL/CommonType.h"
#include "TRL/AttributeVariable.h"
#include "TRL/UniformVariable.h"


namespace TRL
{


class GpuShader;
class GpuTexture;


class GpuProgram
{
public:
    bool Init(GpuShader& vertShader, GpuShader& fragShader);
    const ToyUtility::List<UniformVariable>& GetUniforms() const;
    const ToyUtility::List<AttributeVariable>& GetAttributes() const;
    const UniformVariable& FindUniform(const ToyUtility::String& name) const;
    const AttributeVariable& FindAttribute(const ToyUtility::String& name) const;

    void SetUniform(const UniformVariable& variable, GpuFloat x);
    void SetUniform(const UniformVariable& variable, GpuFloat x, GpuFloat y);
    void SetUniform(const UniformVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z);
    void SetUniform(const UniformVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z, GpuFloat w);
    void SetUniform(const UniformVariable& variable, GpuInt x);
    void SetUniform(const UniformVariable& variable, GpuInt x, GpuInt y);
    void SetUniform(const UniformVariable& variable, GpuInt x, GpuInt y, GpuInt z);
    void SetUniform(const UniformVariable& variable, GpuInt x, GpuInt y, GpuInt z, GpuInt w);
    void SetUniform(const UniformVariable& variable, GpuUInt x);
    void SetUniform(const UniformVariable& variable, GpuUInt x, GpuUInt y);
    void SetUniform(const UniformVariable& variable, GpuUInt x, GpuUInt y, GpuUInt z);
    void SetUniform(const UniformVariable& variable, GpuUInt x, GpuUInt y, GpuUInt z, GpuUInt w);

    void SetUniformArray(const UniformVariable& variable, GpuSizei arrayLength,
        GpuVariableComponentSize componentSize,
        const GpuFloat* values);
    void SetUniformArray(const UniformVariable& variable, GpuSizei arrayLength,
        GpuVariableComponentSize componentSize,
        const GpuInt* values);
    void SetUniformArray(const UniformVariable& variable, GpuSizei arrayLength,
        GpuVariableComponentSize componentSize,
        const GpuUInt* values);

    void SetUniformMatrix2Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix3Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix4Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix2x3Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix3x2Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix2x4Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix4x2Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix3x4Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);
    void SetUniformMatrix4x3Array(const UniformVariable& variable, GpuSizei arrayLength, bool transpose,
        const GpuFloat* values);

    void SetUniformTex(const UniformVariable& variable, const GpuTexture& texture, int textureUnit);

    void Destory();
    

    friend class RenderAPI;

public:
    struct AttributeUniformInfo
    {
        ToyUtility::List<UniformVariable> Uniforms;
        ToyUtility::List<AttributeVariable> Attributes;
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