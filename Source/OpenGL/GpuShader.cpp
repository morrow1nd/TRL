#include "TRL/GpuShader.h"
#include "glad/glad.h"


namespace TRL
{


bool GpuShader::Init(const ToyUtility::String& sourceCode, GpuShaderType type)
{
    m_CompiledSucc = false;

    m_ShaderInner = glCreateShader(type);
    if (m_ShaderInner == 0)
    {
        m_CompileLog = "glCreateShader(" + std::to_string(type) + ") return 0";
        return false;
    }

    const char* code = sourceCode.c_str();

    glShaderSource(m_ShaderInner, 1, &code, NULL);

    glCompileShader(m_ShaderInner);

    GLint compiled;
    glGetShaderiv(m_ShaderInner, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(m_ShaderInner, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            //char* infoLog = malloc(sizeof(char) * infoLen); // TODO
            char infoLog[1024];
            glGetShaderInfoLog(m_ShaderInner, infoLen, NULL, infoLog);
            //m_CompileLog = ToyUtility::String(infoLog);
            m_CompileLog = infoLog;
        }
        
        glDeleteShader(m_ShaderInner);
        
        return false;
    }

    m_CompiledSucc = true;
    return true;
}

bool GpuShader::IsCompiledSucc() const
{
    return m_CompiledSucc;
}

const ToyUtility::String & GpuShader::GetCompileLogInfo() const
{
    return m_CompileLog;
}

GpuShaderType GpuShader::GetShaderType() const
{
    GLint param;
    glGetShaderiv(m_ShaderInner, GL_SHADER_TYPE, &param);
    return (GpuShaderType)param;
}

void GpuShader::Destory()
{
    glDeleteShader(m_ShaderInner);
}


} // end of namespace TRL