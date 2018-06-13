#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Math/Matrix4.h"

#include "TRLConfig.h"
#include "TRL/TRLCommonType.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/AttributeUniformInfo.h"


namespace TRL
{


using ToyUtility::String;
using ToyUtility::List;


class RenderAPI
{
public:
    static int GetGpuDataTypeSize(GpuDataType dataType);


public:
    virtual ~RenderAPI() = default;

    virtual ToyRenderType           UsedNativeApiType() const = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuBuffer

    virtual GpuBufferHandle         GpuBufferCreate() = 0;
    //virtual void                    GpuBufferBind(GpuBufferHandle buffer, GpuBufferType bufferType) = 0;
    //virtual GpuBufferType           GpuBufferGetType(GpuBufferHandle buffer) const = 0;
    virtual void                    GpuBufferSendData(GpuBufferHandle buffer, const void* data, int size,
                                        GpuBufferDataType dataType) = 0;
    virtual void                    GpuBufferSendSubData(GpuBufferHandle buffer,
                                        const void* data, int size, int offset) = 0;
    virtual int                     GpuBufferGetDataSize(GpuBufferHandle buffer) const = 0;
    virtual void                    GpuBufferCleanData(GpuBufferHandle buffer) const = 0;
    virtual void                    GpuBufferDestory(GpuBufferHandle buffer) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuShader

    virtual GpuShaderHandle         GpuShaderCreate(const String& rawSourceCode, GpuShaderType type) = 0;
    virtual bool                    GpuShaderIsCompiledSucc(GpuShaderHandle shader) const = 0;
    virtual const String&           GpuShaderGetCompileLogInfo(GpuShaderHandle shader) const = 0;
    virtual GpuShaderType           GpuShaderGetType(GpuShaderHandle shader) const = 0;
    virtual void                    GpuShaderDestory(GpuShaderHandle shader) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuProgram

    virtual void                    GpuProgramActive(GpuProgramHandle program) = 0;
    virtual bool                    GpuProgramIsActived(GpuProgramHandle program) const = 0;
    virtual GpuProgramHandle        GpuProgramCreate(GpuShaderHandle vertShader, GpuShaderHandle fragShader) = 0;
    virtual bool                    GpuProgramIsLinkedSucc(GpuProgramHandle program) const = 0;
    virtual const AttributeUniformInfo&
                                    GpuProgramGetAttributeUniformInfo(GpuProgramHandle program) const = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        float x) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        float x, float y) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        float x, float y, float z) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        float x, float y, float z, float w) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 x) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 x, uint32 y) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 x, uint32 y, uint32 z) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 x, uint32 y, uint32 z, uint32 w) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        int32 x) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        int32 x, int32 y) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        int32 x, int32 y, int32 z) = 0;
    virtual void                    GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable& variable,
                                        int32 x, int32 y, int32 z, int32 w) = 0;
    virtual void                    GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arryLength, GpuVariableComponentSize componentSize, const float* values) = 0;
    virtual void                    GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arryLength, GpuVariableComponentSize componentSize, const int32* values) = 0;
    virtual void                    GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arryLength, GpuVariableComponentSize componentSize, const uint32* values) = 0;
    virtual void                    GpuProgramSetUniformMatrix2Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix3Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix4Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix2x3Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix3x2Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix2x4Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix4x2Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix3x4Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformMatrix4x3Array(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, const float* values, bool needTranspose = false) = 0;
    virtual void                    GpuProgramSetUniformTexture(GpuProgramHandle program, const UniformVariable& variable,
                                        GpuTextureHandle texture, GpuTextureUnit textureUnit) = 0;
    virtual void                    GpuProgramDestory(GpuProgramHandle program) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuAttributeData

    virtual GpuAttributeDataHandle  GpuAttributeDataCreate() = 0;
    virtual void                    GpuAttributeDataSetIndicesBuffer(GpuAttributeDataHandle attributeData,
                                        GpuBufferHandle ebo, int indicesNumber, GpuDataType type) = 0;
    virtual void                    SetAttributeArray(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        GpuBufferHandle vbo,
                                        GpuVariableComponentSize componentSize,
                                        GpuDataType typeOfComponent,
                                        NormalizeActionType normalizeAction,
                                        int stride,
                                        int beginOffset) = 0;
    virtual void                    EnableAttributeArray(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable, bool enable) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        float x) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        float x, float y) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        float x, float y, float z) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        float x, float y, float z, float w) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        uint32 x, uint32 y, uint32 z, uint32 w) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        int32 x, int32 y, int32 z, int32 w) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        GpuVariableComponentSize componentSize, const float* values) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        const uint32* values) = 0;
    virtual void                    SetConstantAttribute(GpuAttributeDataHandle attributeData,
                                        const AttributeVariable& variable,
                                        const int32* values) = 0;
    virtual void                    GpuAttributeDataDestory(GpuAttributeDataHandle attributeData) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuTexture

    virtual GpuTexture2DHandle      GpuTexture2DCreate() = 0;
    // @level: specifies which mip level to load. The first level is specified by 0
    virtual void                    GpuTexture2DSendImage(GpuTexture2DHandle texture2D,
                                        GpuTextureBaseFormat internalFormat, uint32 width, uint32 height,
                                        PixelFormat format, PixelDataType type, const void* data,
                                        int level = 0) = 0;
    virtual void                    GpuTexture2DSetMinFilter(GpuTexture2DHandle texture2D, GpuTextureMinFilterMode filterMode) = 0;
    virtual void                    GpuTexture2DSetMagFilter(GpuTexture2DHandle texture2D, GpuTextureMagFilterMode filterMode) = 0;
    virtual void                    GpuTexture2DSetWrapS(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode) = 0;
    virtual void                    GpuTexture2DSetWrapR(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode) = 0;
    virtual void                    GpuTexture2DSetWrapT(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode) = 0;
    // Specifies the index of the lowest defined mipmap level. The initial value is 0.
    virtual void                    GpuTexture2DSetBaseLevel(GpuTexture2DHandle texture2D,
                                        int level) = 0;
    // more: compare_func, compare_mode, min_filter, max_filter, min_lod, max_lod, max_level, swizzle_(rgba)
    // Automatic generate mipmap
    virtual void                    GpuTexture2DGenerateMipmap(GpuTexture2DHandle texture2D) = 0;
    virtual void                    GpuTexture2DDestory(GpuTexture2DHandle texture2D) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // Drawing function

    virtual void DrawIndices(GpuPrimitiveType mode, const AttributeData& attributeData, int offset = 0) = 0;


    /////////////////////////////////////////////////////////////////////////////////
    // Others

    // Contain a default matrix into a matrix suitable for use by this specific render system.
    virtual void ConvertProjectionMatrix(const ToyUtility::Matrix4& matrix, ToyUtility::Matrix4& dest) const = 0;
};


} // end of namespace TRL