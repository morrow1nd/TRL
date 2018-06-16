#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLCommonType.h"
#include "TRL/AttributeVariable.h"
#include "TRL/UniformVariable.h"


namespace TRL
{

namespace details
{


class OpenGLShader
{

public:
    OpenGLShader()
        :
        m_CompiledSucc(false),
        m_ShaderInner(0),
        m_ShaderType(GPU_SHADER_TYPE_INIT)
    {
    }


public:
    //void Load(void* p, int size);
    bool Init(const ToyUtility::String& rawSourceCode, GpuShaderType type)
    {
        m_CompiledSucc = false;

        m_ShaderType = type;
        m_ShaderInner = glCreateShader(TRL_GL_NATIVE(type));
        if (m_ShaderInner == 0)
        {
            m_CompileLog = "glCreateShader(" + std::to_string(type) + ") return 0";
            return false;
        }

        const char* code = rawSourceCode.c_str();

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
                char infoLog[1024];
                glGetShaderInfoLog(m_ShaderInner, infoLen, NULL, infoLog);
                m_CompileLog = infoLog;
            }

            glDeleteShader(m_ShaderInner);

            return false;
        }

        m_CompiledSucc = true;
        return true;
    }

    bool IsCompiledSucc() const
    {
        return m_CompiledSucc;
    }

    const ToyUtility::String& GetCompileLogInfo() const
    {
        return m_CompileLog;
    }

    GpuShaderType GetShaderType() const
    {
        return m_ShaderType;
    }

    GLint GetNativeShaderType() const
    {
        GLint param;
        glGetShaderiv(m_ShaderInner, GL_SHADER_TYPE, &param);
        return param;
    }

    void Destory()
    {
        glDeleteShader(m_ShaderInner);
    }

    bool IsGeneratedByTRLShader() const
    {
        return m_ShaderInfo.get() != nullptr;
    }

    friend class OpenGLProgram;


private:
    struct ShaderInfo
    {
        ToyUtility::List<UniformVariable> Uniforms;
        ToyUtility::List<AttributeVariable> Attributes;
    };


private:
    bool m_CompiledSucc;
    GLuint m_ShaderInner;
    GpuShaderType m_ShaderType;
    ToyUtility::String m_CompileLog;
    ToyUtility::SPtr<ShaderInfo> m_ShaderInfo;
};


} // end of namespace details

} // end of namespace TRL