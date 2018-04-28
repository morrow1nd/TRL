#include "TRL/GpuProgram.h"
#include "TRL/GpuShader.h"


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
    return true;
}

void GpuProgram::Destory()
{
    glDeleteProgram(m_ProgramInner);
}


} // end of namespace TRL