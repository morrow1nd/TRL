#include "TRL/GpuProgram.h"
#include "TRL/GpuShader.h"
#include "TRL/AttributeVariable.h"
#include "TRL/UniformVariable.h"


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

const ToyUtility::Vector<UniformVariable>& GpuProgram::GetUniforms() const
{
    return m_VertShaderInfo.Uniforms;
}

const ToyUtility::Vector<AttributeVariable>& GpuProgram::GetAttributes() const
{
    return m_VertShaderInfo.Attributes;
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