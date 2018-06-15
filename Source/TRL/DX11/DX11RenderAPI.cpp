#include "TRL/details/DX11/DX11RenderAPI.h"


namespace TRL
{

namespace details
{


TRLNativeApiType DX11RenderAPI::UsedNativeApiType() const
{
    return TRLNativeApiType::DX11;
}

GpuBufferHandle DX11RenderAPI::GpuBufferCreate()
{
    return GpuBufferHandle(0);
}

void DX11RenderAPI::GpuBufferSendData(GpuBufferHandle buffer, GpuBufferType bufferType, const void * data, int byteSize, GpuBufferDataType dataType)
{
}

void DX11RenderAPI::GpuBufferSendSubData(GpuBufferHandle buffer, const void * data, int byteSize, int offset)
{
}

void DX11RenderAPI::GpuBufferCleanData(GpuBufferHandle buffer) const
{
}

void DX11RenderAPI::GpuBufferDestory(GpuBufferHandle buffer)
{
}

GpuShaderHandle DX11RenderAPI::GpuShaderCreate(const String & rawSourceCode, GpuShaderType type)
{
    return GpuShaderHandle(0);
}

bool DX11RenderAPI::GpuShaderIsCompiledSucc(GpuShaderHandle shader) const
{
    return false;
}

const String & DX11RenderAPI::GpuShaderGetCompileErrorInfo(GpuShaderHandle shader) const
{
    // TODO: insert return statement here
}

GpuShaderType DX11RenderAPI::GpuShaderGetType(GpuShaderHandle shader) const
{
    return GpuShaderType();
}

void DX11RenderAPI::GpuShaderDestory(GpuShaderHandle shader)
{
}

GpuProgramHandle DX11RenderAPI::GpuProgramCreate(GpuShaderHandle vertShader, GpuShaderHandle fragShader)
{
    return GpuProgramHandle(0);
}

bool DX11RenderAPI::GpuProgramIsLinkedSucc(GpuProgramHandle program) const
{
    return false;
}

const String & DX11RenderAPI::GpuProgramGetLinkErrorInfo(GpuProgramHandle program) const
{
    // TODO: insert return statement here
}

const AttributeUniformInfo & DX11RenderAPI::GpuProgramGetAttributeUniformInfo(GpuProgramHandle program) const
{
    // TODO: insert return statement here
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y, float z)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y, float z, float w)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y, uint32 z)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y, uint32 z, uint32 w)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y, int32 z)
{
}

void DX11RenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y, int32 z, int32 w)
{
}

void DX11RenderAPI::GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, GpuVariableComponentSize componentSize, const float * values)
{
}

void DX11RenderAPI::GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, GpuVariableComponentSize componentSize, const int32 * values)
{
}

void DX11RenderAPI::GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, GpuVariableComponentSize componentSize, const uint32 * values)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix2x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix3x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix2x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix4x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix3x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix4x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
}

void DX11RenderAPI::GpuProgramSetUniformTexture(GpuProgramHandle program, const UniformVariable & variable, GpuTextureHandle texture, GpuTextureUnit textureUnit)
{
}

void DX11RenderAPI::GpuProgramDestory(GpuProgramHandle program)
{
}

GpuAttributeDataHandle DX11RenderAPI::GpuAttributeDataCreate()
{
    return GpuAttributeDataHandle(0);
}

void DX11RenderAPI::GpuAttributeDataSetIndicesBuffer(GpuAttributeDataHandle attributeData, GpuBufferHandle ebo, int indicesNumber, GpuDataType type)
{
}

void DX11RenderAPI::SetAttributeArray(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, GpuBufferHandle vbo, GpuVariableComponentSize componentSize, GpuDataType typeOfComponent, NormalizeActionType normalizeAction, int stride, int beginOffset)
{
}

void DX11RenderAPI::EnableAttributeArray(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, bool enable)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y, float z)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y, float z, float w)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, uint32 x, uint32 y, uint32 z, uint32 w)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, int32 x, int32 y, int32 z, int32 w)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, GpuVariableComponentSize componentSize, const float * values)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, const uint32 * values)
{
}

void DX11RenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, const int32 * values)
{
}

void DX11RenderAPI::GpuAttributeDataDestory(GpuAttributeDataHandle attributeData)
{
}

GpuTexture2DHandle DX11RenderAPI::GpuTexture2DCreate()
{
    return GpuTexture2DHandle();
}

void DX11RenderAPI::GpuTexture2DSendImage(GpuTexture2DHandle texture2D, GpuTextureBaseFormat internalFormat, uint32 width, uint32 height, PixelFormat format, PixelDataType type, const void * data, int level = 0)
{
}

void DX11RenderAPI::GpuTexture2DSetMinFilter(GpuTexture2DHandle texture2D, GpuTextureMinFilterMode filterMode)
{
}

void DX11RenderAPI::GpuTexture2DSetMagFilter(GpuTexture2DHandle texture2D, GpuTextureMagFilterMode filterMode)
{
}

void DX11RenderAPI::GpuTexture2DSetWrapS(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode)
{
}

void DX11RenderAPI::GpuTexture2DSetWrapR(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode)
{
}

void DX11RenderAPI::GpuTexture2DSetWrapT(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode)
{
}

void DX11RenderAPI::GpuTexture2DSetBaseLevel(GpuTexture2DHandle texture2D, int level)
{
}

void DX11RenderAPI::GpuTexture2DGenerateMipmap(GpuTexture2DHandle texture2D)
{
}

void DX11RenderAPI::GpuTexture2DDestory(GpuTexture2DHandle texture2D)
{
}

void DX11RenderAPI::DrawIndices(GpuProgramHandle program, GpuAttributeDataHandle attributeData, GpuPrimitiveType mode, int offset = 0)
{
}

void DX11RenderAPI::ConvertProjectionMatrix(const ToyUtility::Matrix4 & matrix, ToyUtility::Matrix4 & dest) const
{
}


} // end of namespace details

} // end of namespace TRL