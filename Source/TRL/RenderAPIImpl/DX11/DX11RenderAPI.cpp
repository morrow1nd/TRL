#include "TRL/details/RenderAPIImpl/DX11/DX11RenderAPI.h"


// #pragma comment(lib,"d3dcompiler.lib")

namespace TRL
{

namespace details
{


TRLNativeApiType DX11RenderAPI::UsedNativeApiType() const
{
    return TRLNativeApiType::DX11;
}

GpuBufferHandle DX11RenderAPI::GpuBufferCreate(const GPU_BUFFER_DESC& desc)
{
    ID3D11Buffer* pBuffer;

    D3D11_USAGE bdUsage = D3D11_USAGE_DEFAULT;
    UINT CpuAccessFlags = 0;

    switch (desc.Access)
    {
    case GpuBufferAccessType::GpuRead:
        bdUsage = D3D11_USAGE_IMMUTABLE;
        break;
    case GpuBufferAccessType::CpuWrite_GpuRead:
        bdUsage = D3D11_USAGE_DYNAMIC;
        CpuAccessFlags |= D3D11_CPU_ACCESS_WRITE;
        break;
    case GpuBufferAccessType::GpuWrite_CpuRead:
        bdUsage = D3D11_USAGE_STAGING;
        CpuAccessFlags |= D3D11_CPU_ACCESS_READ;
        break;
    default: assert(false); break; // TODOH
    }

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = bdUsage;
    bd.ByteWidth = desc.InitData.Size;
    bd.BindFlags = DX11ToNative::Convert(desc.BufferType);
    bd.CPUAccessFlags = CpuAccessFlags;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = desc.InitData.SysMem;
    HRESULT hr = m_D3DDevice->CreateBuffer(&bd, &InitData, &pBuffer);
    if (FAILED(hr))
        return GpuBufferHandle(GpuObjectHandle::EmptyId);

    auto h = m_BufferMgr.New();
    auto& buffer = m_BufferMgr.Get(h);
    buffer.D3D11Buffer = pBuffer;
    buffer.D3D11Usage = bdUsage;
    buffer.Access = desc.Access;
    buffer.BufferType = desc.BufferType;
    buffer.ModifyHint = desc.ModifyHint;

    return h;
}

void DX11RenderAPI::GpuBufferSendData(GpuBufferHandle buffer, const BYTE_DATA_DESC& data)
{
    auto& b = m_BufferMgr.Get(buffer);

    if (b.CanUpdateByCpu())
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
        //	Disable GPU access to the vertex buffer data.
        m_D3DDeviceContext->Map(b.D3D11Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        //	Update the vertex buffer here.
        memcpy(mappedResource.pData, data.SysMem, data.Size);
        //	Reenable GPU access to the vertex buffer data.
        m_D3DDeviceContext->Unmap(b.D3D11Buffer, 0);
    }
    else
    {
        assert(false); // TODOH
    }
}

void DX11RenderAPI::GpuBufferSendSubData(GpuBufferHandle buffer, const BYTE_DATA_DESC& data, int offset)
{
    auto& b = m_BufferMgr.Get(buffer);

    if (b.CanUpdateByCpu())
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
        //	Disable GPU access to the vertex buffer data.
        m_D3DDeviceContext->Map(b.D3D11Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        //	Update the vertex buffer here.
        // TODOH: check array range
        memcpy(((char*)mappedResource.pData + offset), data.SysMem, data.Size);
        //	Reenable GPU access to the vertex buffer data.
        m_D3DDeviceContext->Unmap(b.D3D11Buffer, 0);
    }
    else
    {
        assert(false); // TODOH
    }
}

void DX11RenderAPI::GpuBufferCleanData(GpuBufferHandle buffer) const
{
    // Nothing
}

void DX11RenderAPI::GpuBufferDestory(GpuBufferHandle buffer)
{
    auto& b = m_BufferMgr.Get(buffer);
    b.D3D11Buffer->Release();

    m_BufferMgr.Destory(buffer);
}

GpuShaderHandle DX11RenderAPI::GpuShaderCreate(const GPU_SHADER_DESC& desc)
{
    auto h = m_ShaderMgr.New();
    auto& shader = m_ShaderMgr.Get(h);

    shader.ShaderType = desc.ShaderType;

    // Compile the shader
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//    // Setting this flag improves the shader debugging experience, but still allows 
//    // the shaders to be optimized and to run exactly the way they will run in 
//    // the release configuration of this program.
//    dwShaderFlags |= D3DCOMPILE_DEBUG;
//#endif
    if (desc.DebugMode)
    {
        dwShaderFlags |= D3DCOMPILE_DEBUG;
    }

    ID3DBlob* pErrorBlob;
    hr = D3DCompile(desc.SourceCode.c_str(),
        desc.SourceCode.size(),
        NULL,
        NULL,
        NULL,
        "dx11_vs_main",
        "vs_4_0",
        dwShaderFlags,
        0,
        &shader.Blob,
        &pErrorBlob
    );
    if (FAILED(hr))
    {
        if (pErrorBlob != NULL)
        {
            shader.IsCompileSucc = false;
            shader.CompileLogInfo = (char*)pErrorBlob->GetBufferPointer();

            pErrorBlob->Release();
        }
        return GpuShaderHandle(GpuObjectHandle::EmptyId);
    }

    ID3D11VertexShader* vertexShader = nullptr;
    ID3D11PixelShader* pixelShader = nullptr;
    if (desc.ShaderType == GpuShaderType::GPU_VERTEX_SHADER)
    {
        hr = m_D3DDevice->CreateVertexShader(shader.Blob->GetBufferPointer(), shader.Blob->GetBufferSize(), NULL, &vertexShader);
        if (FAILED(hr))
        {
            shader.IsCompileSucc = false;
            shader.CompileLogInfo = "m_D3DDevice->CreateVertexShader fail " + hr;
        }
        shader.D3DShaderPtr.VertexShader = vertexShader;
    }
    else if (desc.ShaderType == GpuShaderType::GPU_FRAGMENT_SHADER)
    {
        hr = m_D3DDevice->CreatePixelShader(shader.Blob->GetBufferPointer(), shader.Blob->GetBufferSize(), NULL, &pixelShader);
        if (FAILED(hr))
        {
            shader.IsCompileSucc = false;
            shader.CompileLogInfo = "m_D3DDevice->CreatePixelShader fail " + hr;
        }
        shader.D3DShaderPtr.PixelShader = pixelShader;
    }

    return h;
}

bool DX11RenderAPI::GpuShaderIsCompiledSucc(GpuShaderHandle shader) const
{
    auto& s = m_ShaderMgr.Get(shader);
    return s.IsCompileSucc;
}

const String & DX11RenderAPI::GpuShaderGetCompileErrorInfo(GpuShaderHandle shader) const
{
    auto& s = m_ShaderMgr.Get(shader);
    return s.CompileLogInfo;
}

GpuShaderType DX11RenderAPI::GpuShaderGetType(GpuShaderHandle shader) const
{
    auto& s = m_ShaderMgr.Get(shader);
    return s.ShaderType;
}

void DX11RenderAPI::GpuShaderDestory(GpuShaderHandle shader)
{
    auto& s = m_ShaderMgr.Get(shader);

    if (s.Blob)
    {
        s.Blob->Release();
        s.Blob = nullptr;
    }
    if (s.ShaderType == GpuShaderType::GPU_VERTEX_SHADER)
    {
        s.D3DShaderPtr.VertexShader->Release();
        s.D3DShaderPtr.VertexShader = nullptr;
    }
    else if (s.ShaderType == GpuShaderType::GPU_FRAGMENT_SHADER)
    {
        s.D3DShaderPtr.PixelShader->Release();
        s.D3DShaderPtr.PixelShader = nullptr;
    }

    m_ShaderMgr.Destory(shader);
}

GpuProgramHandle DX11RenderAPI::GpuProgramCreate(GpuShaderHandle _vertShader, GpuShaderHandle _fragShader)
{
    auto h = m_ProgramMgr.New();
    auto& program = m_ProgramMgr.Get(h);

    program.VertexShader = _vertShader;
    program.FragShader = _fragShader;


    return h;
}

bool DX11RenderAPI::GpuProgramIsLinkedSucc(GpuProgramHandle program) const
{
    return true;
}

const String & DX11RenderAPI::GpuProgramGetLinkErrorInfo(GpuProgramHandle program) const
{
    return "";
}

const AttributeUniformInfo & DX11RenderAPI::GpuProgramGetAttributeUniformInfo(GpuProgramHandle program) const
{
    // TODO: insert return statement here
    return AttributeUniformInfo();
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

void DX11RenderAPI::GpuProgramSetUniformMatrix2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix2x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix3x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix2x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix4x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix3x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
{
}

void DX11RenderAPI::GpuProgramSetUniformMatrix4x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose)
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

void DX11RenderAPI::GpuTexture2DSendImage(GpuTexture2DHandle texture2D, GpuTextureBaseFormat internalFormat, uint32 width, uint32 height, PixelFormat format, PixelDataType type, const void * data, int level)
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

void DX11RenderAPI::DrawIndices(GpuProgramHandle program, GpuAttributeDataHandle attributeData, GpuPrimitiveType mode, int offset)
{
}

void DX11RenderAPI::ConvertProjectionMatrix(const ToyUtility::Matrix4 & matrix, ToyUtility::Matrix4 & dest) const
{
}


} // end of namespace details

} // end of namespace TRL