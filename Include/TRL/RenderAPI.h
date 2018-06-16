#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Math/Matrix4.h"

#include "TRLConfig.h"
#include "TRL/TRLCommonType.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/AttributeUniformInfo.h"
#include "TRL/DataClasses.h"
#include "TRL/details/VGI/VGI.h"

#include <Windows.h>
namespace TRL
{


using ToyUtility::String;
using ToyUtility::List;


class RenderAPI
{
public:
    static int GetGpuDataTypeSize(GpuDataType dataType);

    static ToyUtility::SPtr<RenderAPI> CreateDefaultRenderAPI();
    static ToyUtility::SPtr<RenderAPI> CreateRenderAPI(TRLNativeApiType type);


public:
    virtual ~RenderAPI() = default;


public:
    /////////////////////////////////////////////////////////////////////////////////
    // RenderAPI

    virtual TRLNativeApiType        UsedNativeApiType() const = 0;

    virtual void                    StartUp(HINSTANCE hInstance, WNDPROC wndProc);
    virtual void                    ShutDown();

    /////////////////////////////////////////////////////////////////////////////////
    // Adapter(Video card), Monitor

    AdapterHandle                   GetDefaultAdapter();
    const List<AdapterHandle>&      GetAdapters();
    bool                            AdapterGetDesc(AdapterHandle adapter, AdapterDesc& desc);

    List<MonitorHandle>             AdapterGetMonitors(AdapterHandle adapter);
    void                            MonitorGetDesc(MonitorHandle monitor, MonitorDesc& desc);

    /////////////////////////////////////////////////////////////////////////////////
    // Window

    WindowHandle                    WindowCreate(const WINDOW_CREATE_DESC& desc);
    void                            WindowDestory(WindowHandle window);
    void                            WindowSetMain(WindowHandle window);
    WindowHandle                    WindowGetMain() const;
    void                            WindowSetTitle(WindowHandle window, const String& title);
    void                            WindowSetSize(WindowHandle window, uint32 width, uint32 height);
    void                            WindowGetSize(WindowHandle window, uint32* width, uint32* height) const;
    void                            WindowSetPosition(WindowHandle window, int32 x, int32 y);
    void                            WindowGetPosition(WindowHandle window, int32* x, int32* y);
    void                            WindowSetVisible(WindowHandle window, bool visible);
    void                            WindowFocus(WindowHandle window);
    // @syncInterval: An integer that specifies the how to synchronize presentation of a frame with the
    //      vertical blank.Values are :
    //      0 - The presentation occurs immediately, there is no synchronization.
    //      1, 2, 3, 4 - Synchronize presentation after the n'th vertical blank. 
    void                            WindowPresent(WindowHandle window, uint32 syncInterval);

    // TODO: SDL:ScreenSaver, 

    /////////////////////////////////////////////////////////////////////////////////
    // --
    void                            SetViewport(uint32 topLeftX, uint32 topLeftY, uint32 width, uint32 height);

    /////////////////////////////////////////////////////////////////////////////////
    // GpuBuffer

    virtual GpuBufferHandle         GpuBufferCreate() = 0;
    virtual void                    GpuBufferSendData(GpuBufferHandle buffer,
                                        GpuBufferType bufferType,
                                        const void* data, int byteSize, GpuBufferDataType dataType) = 0;
    virtual void                    GpuBufferSendSubData(GpuBufferHandle buffer,
                                        const void* data, int byteSize, int offset) = 0;
    virtual void                    GpuBufferCleanData(GpuBufferHandle buffer) const = 0;
    virtual void                    GpuBufferDestory(GpuBufferHandle buffer) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuShader

    virtual GpuShaderHandle         GpuShaderCreate(const String& rawSourceCode, GpuShaderType type) = 0;
    virtual bool                    GpuShaderIsCompiledSucc(GpuShaderHandle shader) const = 0;
    virtual const String&           GpuShaderGetCompileErrorInfo(GpuShaderHandle shader) const = 0;
    virtual GpuShaderType           GpuShaderGetType(GpuShaderHandle shader) const = 0;
    virtual void                    GpuShaderDestory(GpuShaderHandle shader) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // GpuProgram

    virtual GpuProgramHandle        GpuProgramCreate(GpuShaderHandle vertShader, GpuShaderHandle fragShader) = 0;
    virtual bool                    GpuProgramIsLinkedSucc(GpuProgramHandle program) const = 0;
    virtual const String&           GpuProgramGetLinkErrorInfo(GpuProgramHandle program) const = 0;
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
                                        uint32 arrayLength, GpuVariableComponentSize componentSize, const float* values) = 0;
    virtual void                    GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, GpuVariableComponentSize componentSize, const int32* values) = 0;
    virtual void                    GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable& variable,
                                        uint32 arrayLength, GpuVariableComponentSize componentSize, const uint32* values) = 0;
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
    // GpuAttributeData(VAO)

    virtual GpuAttributeDataHandle  GpuAttributeDataCreate() = 0;
    virtual void                    GpuAttributeDataSetIndicesBuffer(GpuAttributeDataHandle attributeData,
                                        GpuBufferHandle ebo, int indicesNumber, GpuDataType type) = 0;
    // @stride: in bytes
    // @beginOffset: in bytes
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

    virtual void                    DrawIndices(GpuProgramHandle program, GpuAttributeDataHandle attributeData, GpuPrimitiveType mode, int offset = 0) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    // Others

    // Contain a default matrix into a matrix suitable for use by this specific render system.
    virtual void                    ConvertProjectionMatrix(const ToyUtility::Matrix4& matrix, ToyUtility::Matrix4& dest) const = 0;


private:
    ToyUtility::SPtr<details::VGI> m_VGI;
    IndexedContainer<AdapterHandle, details::Adapter*> m_AdapterMgr;
    List<AdapterHandle> m_AdapterHandles;
    List<details::Adapter*> m_Adapters;
};


} // end of namespace TRL