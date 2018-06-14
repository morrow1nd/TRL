#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/RenderAPI.h"
#include "TRL/details/OpenGL/OpenGLBuffer.h"
#include "TRL/details/OpenGL/OpenGLShader.h"
#include "TRL/details/OpenGL/OpenGLProgram.h"
#include "TRL/details/OpenGL/OpenGLTexture.h"
#include "TRL/details/OpenGL/OpenGLTexture2D.h"
#include "TRL/details/OpenGL/OpenGLAttributeData.h"


namespace TRL
{

namespace details
{


template<typename T>
class OneValue
{
public:
    OneValue()
        :
        m_ValueInited(false)
    { }


    bool IsSame(T value) const
    {
        return m_ValueInited && value == m_Value;
    }

    void SetValue(T value) { m_Value = value; m_ValueInited = true; }


private:
    T m_Value;
    bool m_ValueInited;
};


class OpenGLRenderAPI : public RenderAPI
{
public:
    virtual TRLNativeApiType UsedNativeApiType() const override;
    virtual GpuBufferHandle GpuBufferCreate() override;
    virtual void GpuBufferSendData(GpuBufferHandle buffer, GpuBufferType bufferType, const void * data, int size, GpuBufferDataType dataType) override;
    virtual void GpuBufferSendSubData(GpuBufferHandle buffer, const void * data, int size, int offset) override;
    virtual void GpuBufferCleanData(GpuBufferHandle buffer) const override;
    virtual void GpuBufferDestory(GpuBufferHandle buffer) override;
    virtual GpuShaderHandle GpuShaderCreate(const String & rawSourceCode, GpuShaderType type) override;
    virtual bool GpuShaderIsCompiledSucc(GpuShaderHandle shader) const override;
    virtual const String & GpuShaderGetCompileErrorInfo(GpuShaderHandle shader) const override;
    virtual GpuShaderType GpuShaderGetType(GpuShaderHandle shader) const override;
    virtual void GpuShaderDestory(GpuShaderHandle shader) override;
    virtual GpuProgramHandle GpuProgramCreate(GpuShaderHandle vertShader, GpuShaderHandle fragShader) override;
    virtual bool GpuProgramIsLinkedSucc(GpuProgramHandle program) const override;
    virtual const String & GpuProgramGetLinkErrorInfo(GpuProgramHandle program) const override;
    virtual const AttributeUniformInfo & GpuProgramGetAttributeUniformInfo(GpuProgramHandle program) const override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y, float z) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y, float z, float w) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y, uint32 z) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y, uint32 z, uint32 w) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y, int32 z) override;
    virtual void GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y, int32 z, int32 w) override;
    virtual void GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arryLength, GpuVariableComponentSize componentSize, const float * values) override;
    virtual void GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arryLength, GpuVariableComponentSize componentSize, const int32 * values) override;
    virtual void GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arryLength, GpuVariableComponentSize componentSize, const uint32 * values) override;
    virtual void GpuProgramSetUniformMatrix2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix2x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix3x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix2x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix4x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix3x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformMatrix4x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false) override;
    virtual void GpuProgramSetUniformTexture(GpuProgramHandle program, const UniformVariable & variable, GpuTextureHandle texture, GpuTextureUnit textureUnit) override;
    virtual void GpuProgramDestory(GpuProgramHandle program) override;
    virtual GpuAttributeDataHandle GpuAttributeDataCreate() override;
    virtual void GpuAttributeDataSetIndicesBuffer(GpuAttributeDataHandle attributeData, GpuBufferHandle ebo, int indicesNumber, GpuDataType type) override;
    virtual void SetAttributeArray(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, GpuBufferHandle vbo, GpuVariableComponentSize componentSize, GpuDataType typeOfComponent, NormalizeActionType normalizeAction, int stride, int beginOffset) override;
    virtual void EnableAttributeArray(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, bool enable) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y, float z) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y, float z, float w) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, uint32 x, uint32 y, uint32 z, uint32 w) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, int32 x, int32 y, int32 z, int32 w) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, GpuVariableComponentSize componentSize, const float * values) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, const uint32 * values) override;
    virtual void SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, const int32 * values) override;
    virtual void GpuAttributeDataDestory(GpuAttributeDataHandle attributeData) override;
    virtual GpuTexture2DHandle GpuTexture2DCreate() override;
    virtual void GpuTexture2DSendImage(GpuTexture2DHandle texture2D, GpuTextureBaseFormat internalFormat, uint32 width, uint32 height, PixelFormat format, PixelDataType type, const void * data, int level = 0) override;
    virtual void GpuTexture2DSetMinFilter(GpuTexture2DHandle texture2D, GpuTextureMinFilterMode filterMode) override;
    virtual void GpuTexture2DSetMagFilter(GpuTexture2DHandle texture2D, GpuTextureMagFilterMode filterMode) override;
    virtual void GpuTexture2DSetWrapS(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode) override;
    virtual void GpuTexture2DSetWrapR(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode) override;
    virtual void GpuTexture2DSetWrapT(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode) override;
    virtual void GpuTexture2DSetBaseLevel(GpuTexture2DHandle texture2D, int level) override;
    virtual void GpuTexture2DGenerateMipmap(GpuTexture2DHandle texture2D) override;
    virtual void GpuTexture2DDestory(GpuTexture2DHandle texture2D) override;
    virtual void DrawIndices(GpuProgramHandle program, GpuAttributeDataHandle attributeData, GpuPrimitiveType mode, int offset = 0) override;
    virtual void ConvertProjectionMatrix(const ToyUtility::Matrix4 & matrix, ToyUtility::Matrix4 & dest) const override;


private:
    void _ActiveGpuAttributeData(GpuAttributeDataHandle h);
    void _ActiveGpuAttributeData(OpenGLAttributeData attributeData);
    void _ActiveGpuProgram(GpuProgramHandle h);
    void _ActiveTexture2D(GpuTexture2DHandle h);
    void _ActiveTexture2D(OpenGLTexture2D tex2D);


private:
    IndexedContainer<GpuBufferHandle, OpenGLBuffer> m_BufferMgr;
    IndexedContainer<GpuShaderHandle, OpenGLShader> m_ShaderMgr;
    IndexedContainer<GpuProgramHandle, OpenGLProgram> m_ProgramMgr;
    IndexedContainer<GpuTexture2DHandle, OpenGLTexture2D> m_Texture2DMgr;
    IndexedContainer<GpuAttributeDataHandle, OpenGLAttributeData> m_AttributeDataMgr;

    OneValue<GLuint> m_ActiveGpuProgram;
    OneValue<GLuint> m_ActiveGpuAttributeData; // VAO
    OneValue<GLuint> m_ActiveTexture2D;
};


} // end of namespace details

} // end of namespace TRL