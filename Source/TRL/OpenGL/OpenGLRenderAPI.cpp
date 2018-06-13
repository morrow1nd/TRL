#include "TRL/details/OpenGL/OpenGLRenderAPI.h"


namespace TRL
{

namespace details
{


TRLNativeApiType OpenGLRenderAPI::UsedNativeApiType() const
{
    return TRLNativeApiType::OpenGL;
}

GpuBufferHandle OpenGLRenderAPI::GpuBufferCreate()
{
    auto h = m_BufferMgr.New();
    auto& buffer = m_BufferMgr.Get(h);

    buffer.Init();

    return h;
}

void OpenGLRenderAPI::GpuBufferSendData(GpuBufferHandle buffer, GpuBufferType bufferType, const void * data, int size, GpuBufferDataType dataType)
{
    auto& b = m_BufferMgr.Get(buffer);

    b.Bind(bufferType);
    b.UploadData(data, size, dataType);
}

void OpenGLRenderAPI::GpuBufferSendSubData(GpuBufferHandle buffer, const void * data, int size, int offset)
{
    auto& b = m_BufferMgr.Get(buffer);

    b.Bind();
    b.UploadSubData(data, size, offset);
}

int OpenGLRenderAPI::GpuBufferGetDataSize(GpuBufferHandle buffer) const
{
    return m_BufferMgr.Get(buffer).GetDataSize();
}

void OpenGLRenderAPI::GpuBufferCleanData(GpuBufferHandle buffer) const
{
    m_BufferMgr.Get(buffer).CleanData();
}

void OpenGLRenderAPI::GpuBufferDestory(GpuBufferHandle buffer)
{
    m_BufferMgr.Get(buffer).Destory();
    m_BufferMgr.Destory(buffer);
}

GpuShaderHandle OpenGLRenderAPI::GpuShaderCreate(const String & rawSourceCode, GpuShaderType type)
{
    auto h = m_ShaderMgr.New();
    auto& shader = m_ShaderMgr.Get(h);

    shader.Init(rawSourceCode, type);

    return h;
}

bool OpenGLRenderAPI::GpuShaderIsCompiledSucc(GpuShaderHandle shader) const
{
    auto& s = m_ShaderMgr.Get(shader);
    return s.IsCompiledSucc();
}

const String& OpenGLRenderAPI::GpuShaderGetCompileLogInfo(GpuShaderHandle shader) const
{
    auto& s = m_ShaderMgr.Get(shader);
    return s.GetCompileLogInfo();
}

GpuShaderType OpenGLRenderAPI::GpuShaderGetType(GpuShaderHandle shader) const
{
    auto& s = m_ShaderMgr.Get(shader);
    return s.GetShaderType();
}

void OpenGLRenderAPI::GpuShaderDestory(GpuShaderHandle shader)
{
    m_ShaderMgr.Get(shader).Destory();
    m_ShaderMgr.Destory(shader);
}

GpuProgramHandle OpenGLRenderAPI::GpuProgramCreate(GpuShaderHandle vertShader, GpuShaderHandle fragShader)
{
    auto h = m_ProgramMgr.New();
    auto& program = m_ProgramMgr.Get(h);

    auto& vert = m_ShaderMgr.Get(vertShader);
    auto& frag = m_ShaderMgr.Get(fragShader);

    program.Init(vert, frag);

    return h;
}

bool OpenGLRenderAPI::GpuProgramIsLinkedSucc(GpuProgramHandle program) const
{
    return m_ProgramMgr.Get(program).IsLinkSucc();
}

const AttributeUniformInfo & OpenGLRenderAPI::GpuProgramGetAttributeUniformInfo(GpuProgramHandle program) const
{
    return m_ProgramMgr.Get(program).GetAttributeUniformInfo();
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x)
{
    _ActiveGpuProgram(program);
    glUniform1f(variable.GetLocation(), x);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y)
{
    _ActiveGpuProgram(program);
    glUniform2f(variable.GetLocation(), x, y);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y, float z)
{
    _ActiveGpuProgram(program);
    glUniform3f(variable.GetLocation(), x, y, z);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, float x, float y, float z, float w)
{
    _ActiveGpuProgram(program);
    glUniform4f(variable.GetLocation(), x, y, z, w);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x)
{
    _ActiveGpuProgram(program);
    glUniform1i(variable.GetLocation(), x);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y)
{
    _ActiveGpuProgram(program);
    glUniform2i(variable.GetLocation(), x, y);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y, uint32 z)
{
    _ActiveGpuProgram(program);
    glUniform3i(variable.GetLocation(), x, y, z);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, uint32 x, uint32 y, uint32 z, uint32 w)
{
    _ActiveGpuProgram(program);
    glUniform4i(variable.GetLocation(), x, y, z, w);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x)
{
    _ActiveGpuProgram(program);
    glUniform1ui(variable.GetLocation(), x);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y)
{
    _ActiveGpuProgram(program);
    glUniform2ui(variable.GetLocation(), x, y);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y, int32 z)
{
    _ActiveGpuProgram(program);
    glUniform3ui(variable.GetLocation(), x, y, z);
}

void OpenGLRenderAPI::GpuProgramSetUniform(GpuProgramHandle program, const UniformVariable & variable, int32 x, int32 y, int32 z, int32 w)
{
    _ActiveGpuProgram(program);
    glUniform4ui(variable.GetLocation(), x, y, z, w);
}

void OpenGLRenderAPI::GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, GpuVariableComponentSize componentSize, const float * values)
{
    _ActiveGpuProgram(program);
    // TODO: or use a function pointer list to replace the switch ?
    switch (componentSize)
    {
    case GpuVariableComponentSize::_1:
        glUniform1fv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_2:
        glUniform2fv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_3:
        glUniform3fv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_4:
        glUniform4fv(variable.GetLocation(), arrayLength, values);
        break;
    }
}

void OpenGLRenderAPI::GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, GpuVariableComponentSize componentSize, const int32 * values)
{
    _ActiveGpuProgram(program);
    switch (componentSize)
    {
    case GpuVariableComponentSize::_1:
        glUniform1iv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_2:
        glUniform2iv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_3:
        glUniform3iv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_4:
        glUniform4iv(variable.GetLocation(), arrayLength, values);
        break;
    }
}

void OpenGLRenderAPI::GpuProgramSetUniformArray(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, GpuVariableComponentSize componentSize, const uint32 * values)
{
    _ActiveGpuProgram(program);
    switch (componentSize)
    {
    case GpuVariableComponentSize::_1:
        glUniform1uiv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_2:
        glUniform2uiv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_3:
        glUniform3uiv(variable.GetLocation(), arrayLength, values);
        break;
    case GpuVariableComponentSize::_4:
        glUniform4uiv(variable.GetLocation(), arrayLength, values);
        break;
    }
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix2fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix3fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix4fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix2x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix2x3fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix3x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix3x2fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix2x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix2x4fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix4x2Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix4x2fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix3x4Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix3x4fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformMatrix4x3Array(GpuProgramHandle program, const UniformVariable & variable, uint32 arrayLength, const float * values, bool needTranspose = false)
{
    _ActiveGpuProgram(program);
    glUniformMatrix4x3fv(variable.GetLocation(), arrayLength, needTranspose ? GL_TRUE : GL_FALSE, values);
}

void OpenGLRenderAPI::GpuProgramSetUniformTexture(GpuProgramHandle program, const UniformVariable & variable, GpuTextureHandle texture, GpuTextureUnit textureUnit)
{
    _ActiveGpuProgram(program);
#if(TRL_MORE_RUNTIME_CHECK)
    {
        GLint fragShaderMaxTextureUnit, vertShaderMaxTextureUnit;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &fragShaderMaxTextureUnit);
        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &vertShaderMaxTextureUnit);
        if ((textureUnit >= 0
            && textureUnit < vertShaderMaxTextureUnit
            && textureUnit < fragShaderMaxTextureUnit) == false)
        {
            std::cout << "Error: (textureUnit >= 0 && textureUnit < vertShaderMaxTextureUnit "
                "&& textureUnit < fragShaderMaxTextureUnit) == false\n"
                << "fragShaderMaxTextureUnit: " << fragShaderMaxTextureUnit
                << "\nvertShaderMaxTextureUnit: " << vertShaderMaxTextureUnit
                << "\ninput textureUnit: " << textureUnit << std::endl;
            return;
        }
    }
#endif

    auto textureType = texture.TextureType();
    switch (textureType)
    {
    case GPU_TEXTURE_2D:
        auto& t = m_Texture2DMgr.Get(GpuTexture2DHandle(texture));
        t.ActiveTextureUnit(textureUnit);
        break;
    default:
        assert(false);
        break;
    }

    glUniform1i(variable.GetLocation(), textureUnit);
}

void OpenGLRenderAPI::GpuProgramDestory(GpuProgramHandle program)
{
    m_ProgramMgr.Get(program).Destory();
    m_ProgramMgr.Destory(program);
}

GpuAttributeDataHandle OpenGLRenderAPI::GpuAttributeDataCreate()
{
    auto h = m_AttributeDataMgr.New();
    auto& attributeData = m_AttributeDataMgr.Get(h);

    attributeData.Init();

    return h;
}

void OpenGLRenderAPI::GpuAttributeDataSetIndicesBuffer(GpuAttributeDataHandle attributeData, GpuBufferHandle ebo, int indicesNumber, GpuDataType type)
{
    auto& ebo_ = m_BufferMgr.Get(ebo);
    auto& attributeData_ = m_AttributeDataMgr.Get(attributeData);

    ebo_.Bind();
    attributeData_.GetEBOInfo().DataType = type;
    attributeData_.GetEBOInfo().IndicesNumber = indicesNumber;
}

void OpenGLRenderAPI::SetAttributeArray(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, GpuBufferHandle vbo, GpuVariableComponentSize componentSize, GpuDataType typeOfComponent, NormalizeActionType normalizeAction, int stride, int beginOffset)
{
    _ActiveGpuAttributeData(attributeData);

    auto& vbo_ = m_BufferMgr.Get(vbo);
    vbo_.Bind();

    glEnableVertexAttribArray(variable.GetLocation());
    glVertexAttribPointer(variable.GetLocation(),
        TRL_GL_NATIVE(componentSize),
        TRL_GL_NATIVE(typeOfComponent),
        TRL_GL_NATIVE(normalizeAction),
        stride,
        (const void*)beginOffset);
}

void OpenGLRenderAPI::EnableAttributeArray(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, bool enable)
{
    _ActiveGpuAttributeData(attributeData);

    if (enable)
        glEnableVertexAttribArray(variable.GetLocation());
    else
        glDisableVertexAttribArray(variable.GetLocation());
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttrib1f(variable.GetLocation(), x);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttrib2f(variable.GetLocation(), x, y);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y, float z)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttrib3f(variable.GetLocation(), x, y, z);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, float x, float y, float z, float w)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttrib4f(variable.GetLocation(), x, y, z, w);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, uint32 x, uint32 y, uint32 z, uint32 w)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttribI4ui(variable.GetLocation(), x, y, z, w);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, int32 x, int32 y, int32 z, int32 w)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttribI4i(variable.GetLocation(), x, y, z, w);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, GpuVariableComponentSize componentSize, const float * values)
{
    _ActiveGpuAttributeData(attributeData);

    switch (componentSize)
    {
    case GpuVariableComponentSize::_1:
        glVertexAttrib1fv(variable.GetLocation(), values);
        break;
    case GpuVariableComponentSize::_2:
        glVertexAttrib2fv(variable.GetLocation(), values);
        break;
    case GpuVariableComponentSize::_3:
        glVertexAttrib3fv(variable.GetLocation(), values);
        break;
    case GpuVariableComponentSize::_4:
        glVertexAttrib4fv(variable.GetLocation(), values);
        break;
    default:
        assert(false);
        break;
    }
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, const uint32 * values)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttribI4uiv(variable.GetLocation(), values);
}

void OpenGLRenderAPI::SetConstantAttribute(GpuAttributeDataHandle attributeData, const AttributeVariable & variable, const int32 * values)
{
    _ActiveGpuAttributeData(attributeData);

    glVertexAttribI4iv(variable.GetLocation(), values);
}

void OpenGLRenderAPI::GpuAttributeDataDestory(GpuAttributeDataHandle attributeData)
{
    m_AttributeDataMgr.Get(attributeData).Destory();
    m_AttributeDataMgr.Destory(attributeData);
}

GpuTexture2DHandle OpenGLRenderAPI::GpuTexture2DCreate()
{
    auto h = m_Texture2DMgr.New();
    auto& tex = m_Texture2DMgr.Get(h);

    tex.Init();

    return h;
}

void OpenGLRenderAPI::GpuTexture2DSendImage(GpuTexture2DHandle texture2D, GpuTextureBaseFormat internalFormat, uint32 width, uint32 height, PixelFormat format, PixelDataType type, const void * data, int level)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.UploadImage(internalFormat, width, height, format, type, data, level);    
}

void OpenGLRenderAPI::GpuTexture2DSetMinFilter(GpuTexture2DHandle texture2D, GpuTextureMinFilterMode filterMode)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.SetMinFilter(filterMode);
}

void OpenGLRenderAPI::GpuTexture2DSetMagFilter(GpuTexture2DHandle texture2D, GpuTextureMagFilterMode filterMode)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.SetMagFilter(filterMode);
}

void OpenGLRenderAPI::GpuTexture2DSetWrapS(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.SetWrapS(wrapMode);
}

void OpenGLRenderAPI::GpuTexture2DSetWrapR(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.SetWrapR(wrapMode);
}

void OpenGLRenderAPI::GpuTexture2DSetWrapT(GpuTexture2DHandle texture2D, GpuTextureWrapMode wrapMode)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.SetWrapT(wrapMode);
}

void OpenGLRenderAPI::GpuTexture2DSetBaseLevel(GpuTexture2DHandle texture2D, int level)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.SetBaseLevel(level);
}

void OpenGLRenderAPI::GpuTexture2DGenerateMipmap(GpuTexture2DHandle texture2D)
{
    auto& tex = m_Texture2DMgr.Get(texture2D);

    _ActiveTexture2D(tex);

    tex.GenerateMipmap();
}

void OpenGLRenderAPI::GpuTexture2DDestory(GpuTexture2DHandle texture2D)
{
    m_Texture2DMgr.Get(texture2D).Destory();
    m_Texture2DMgr.Destory(texture2D);
}

void OpenGLRenderAPI::DrawIndices(GpuProgramHandle program, GpuAttributeDataHandle attributeData, GpuPrimitiveType mode, int offset)
{
    auto& attributeData_ = m_AttributeDataMgr.Get(attributeData);

    _ActiveGpuAttributeData(attributeData_);
    _ActiveGpuProgram(program);

    glDrawElements(TRL_GL_NATIVE(mode), attributeData_.GetEBOInfo().IndicesNumber, attributeData_.GetEBOInfo().DataType,
        (const void*)offset);
}

void OpenGLRenderAPI::ConvertProjectionMatrix(const ToyUtility::Matrix4 & matrix, ToyUtility::Matrix4 & dest) const
{
    dest = matrix;
}

void OpenGLRenderAPI::_ActiveGpuAttributeData(GpuAttributeDataHandle h)
{
    _ActiveGpuAttributeData(m_AttributeDataMgr.Get(h));
}

void OpenGLRenderAPI::_ActiveGpuAttributeData(OpenGLAttributeData attributeData)
{
    if (m_ActiveGpuAttributeData.IsSame(attributeData.GetInnerName()) == false)
    {
        glBindVertexArray(attributeData.GetInnerName());
        m_ActiveGpuAttributeData.SetValue(attributeData.GetInnerName());
    }
}

void OpenGLRenderAPI::_ActiveGpuProgram(GpuProgramHandle h)
{
    auto& program = m_ProgramMgr.Get(h);

    if (m_ActiveGpuProgram.IsSame(program.GetInnerName()) == false)
    {
        glUseProgram(program.GetInnerName());
        m_ActiveGpuProgram.SetValue(program.GetInnerName());
    }
}

void OpenGLRenderAPI::_ActiveTexture2D(GpuTexture2DHandle h)
{
    _ActiveTexture2D(m_Texture2DMgr.Get(h));
}

void OpenGLRenderAPI::_ActiveTexture2D(OpenGLTexture2D tex2D)
{
    if (m_ActiveTexture2D.IsSame(tex2D.GetInnerName()) == false)
    {
        tex2D.Bind();
        m_ActiveTexture2D.SetValue(tex2D.GetInnerName());
    }
}


} // end of namespace details

} // end of namespace TRL