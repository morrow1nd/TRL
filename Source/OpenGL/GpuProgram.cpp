#include "TRL/GpuProgram.h"
#include "TRL/GpuShader.h"
#include "TRL/AttributeVariable.h"
#include "TRL/UniformVariable.h"
#include "TRL/GpuTexture.h"

#if (TRL_MORE_RUNTIME_CHECK)
# include <iostream>
#endif


namespace TRL
{


bool GpuProgram::Init(GpuShader& vertShader, GpuShader& fragShader)
{
    m_LinkedSucc = false;

    m_ProgramInner = glCreateProgram();
    if (m_ProgramInner == 0)
    {
        m_LinkLog = "glCreateProgram() return 0";
        return false;
    }

    glAttachShader(m_ProgramInner, vertShader.m_ShaderInner);
    glAttachShader(m_ProgramInner, fragShader.m_ShaderInner);

    glLinkProgram(m_ProgramInner);

    GLint linked;
    glGetProgramiv(m_ProgramInner, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(m_ProgramInner, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            // char* infoLog = maloc(sizeof(char)*infoLen);
            char infoLog[1024];
            glGetProgramInfoLog(m_ProgramInner, infoLen, NULL, infoLog);
            m_LinkLog = infoLog;
        }

        glDeleteProgram(m_ProgramInner);
        return false;
    }

    m_LinkedSucc = true;

    _PrepareAttributeInfos(vertShader, fragShader);
    _PrepareUniformInfos(vertShader, fragShader);

    return true;
}

const ToyUtility::List<UniformVariable>& GpuProgram::GetUniforms() const
{
    return m_VertShaderInfo.Uniforms;
}

const ToyUtility::List<AttributeVariable>& GpuProgram::GetAttributes() const
{
    return m_VertShaderInfo.Attributes;
}

const UniformVariable & GpuProgram::FindUniform(const ToyUtility::String & name) const
{
    for (auto i = m_VertShaderInfo.Uniforms.begin(); i != m_VertShaderInfo.Uniforms.end(); ++i)
    {
        if ((*i).GetName() == name)
        {
            return (*i);
        }
    }

    return UniformVariable::None;
}

const AttributeVariable & GpuProgram::FindAttribute(const ToyUtility::String & name) const
{
    for (auto i = m_VertShaderInfo.Attributes.begin(); i != m_VertShaderInfo.Attributes.end(); ++i)
    {
        if ((*i).GetName() == name)
        {
            return (*i);
        }
    }

    return AttributeVariable::None;
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuFloat x)
{
    glUniform1f(variable.GetLocation(), x);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuFloat x, GpuFloat y)
{
    glUniform2f(variable.GetLocation(), x, y);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuFloat x, GpuFloat y, GpuFloat z)
{
    glUniform3f(variable.GetLocation(), x, y, z);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuFloat x, GpuFloat y, GpuFloat z, GpuFloat w)
{
    glUniform4f(variable.GetLocation(), x, y, z, w);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuInt x)
{
    glUniform1i(variable.GetLocation(), x);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuInt x, GpuInt y)
{
    glUniform2i(variable.GetLocation(), x, y);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuInt x, GpuInt y, GpuInt z)
{
    glUniform3i(variable.GetLocation(), x, y, z);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuInt x, GpuInt y, GpuInt z, GpuInt w)
{
    glUniform4i(variable.GetLocation(), x, y, z, w);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuUInt x)
{
    glUniform1ui(variable.GetLocation(), x);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuUInt x, GpuUInt y)
{
    glUniform2ui(variable.GetLocation(), x, y);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuUInt x, GpuUInt y, GpuUInt z)
{
    glUniform3ui(variable.GetLocation(), x, y, z);
}

void GpuProgram::SetUniform(const UniformVariable & variable, GpuUInt x, GpuUInt y, GpuUInt z, GpuUInt w)
{
    glUniform4ui(variable.GetLocation(), x, y, z, w);
}

void GpuProgram::SetUniformArray(const UniformVariable & variable, GpuSizei arrayLength,
    GpuVariableComponentSize componentSize,
    const GpuFloat * values)
{
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

void GpuProgram::SetUniformArray(const UniformVariable & variable, GpuSizei arrayLength,
    GpuVariableComponentSize componentSize,
    const GpuInt * values)
{
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

void GpuProgram::SetUniformArray(const UniformVariable & variable, GpuSizei arrayLength,
    GpuVariableComponentSize componentSize,
    const GpuUInt * values)
{
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

void GpuProgram::SetUniformMatrix2Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix2fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix3Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix3fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix4Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix4fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix2x3Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix2x3fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix3x2Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix3x2fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix2x4Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix2x4fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix4x2Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix4x2fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix3x4Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix3x4fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformMatrix4x3Array(const UniformVariable & variable, GpuSizei arrayLength,
    bool transpose, const GpuFloat * values)
{
    glUniformMatrix4x3fv(variable.GetLocation(), arrayLength, transpose ? GL_TRUE : GL_FALSE, values);
}

void GpuProgram::SetUniformTex(const UniformVariable& variable, const GpuTexture& texture, int textureUnit)
{
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

    texture.ActiveTexture(textureUnit);
    glUniform1i(variable.GetLocation(), textureUnit);
}

void GpuProgram::Destory()
{
    glDeleteProgram(m_ProgramInner);
}

void GpuProgram::_PrepareUniformInfos(GpuShader& vertShader, GpuShader& fragShader)
{
    if (vertShader.IsGeneratedByTRLShader())
    {
        // TODO
    }
    else
    {
        GLint uniformNum, maxUniformNameLength;
        glGetProgramiv(m_ProgramInner, GL_ACTIVE_UNIFORMS, &uniformNum);
        glGetProgramiv(m_ProgramInner, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLength);

        char name[1024]; // TODO

        for (int index = 0; index < uniformNum; ++index)
        {
            GLint size;
            GLenum type;
            GLint location;

            glGetActiveUniform(m_ProgramInner, index, maxUniformNameLength, NULL, &size, &type, name);
            location = glGetUniformLocation(m_ProgramInner, name);
            m_VertShaderInfo.Uniforms.push_back(UniformVariable(name, location, (GpuDataType)type, size));
        }
    }
}

void GpuProgram::_PrepareAttributeInfos(GpuShader& vertShader, GpuShader& fragShader)
{
    if (vertShader.IsGeneratedByTRLShader())
    {
        // TODO
    }
    else
    {
        GLint attributeNum, maxAttributeNameLength;
        glGetProgramiv(m_ProgramInner, GL_ACTIVE_ATTRIBUTES, &attributeNum);
        glGetProgramiv(m_ProgramInner, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttributeNameLength);

        char name[1024]; // TODO

        for (int index = 0; index < attributeNum; ++index)
        {
            GLint size;
            GLenum type;
            GLint location; // layout

            glGetActiveAttrib(m_ProgramInner, index, maxAttributeNameLength, NULL, &size, &type, name);
            location = glGetAttribLocation(m_ProgramInner, name);
            m_VertShaderInfo.Attributes.push_back(AttributeVariable(name, location, (GpuDataType)type, size));
        }
    }
}


} // end of namespace TRL