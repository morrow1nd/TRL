#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Log/Logger.h"
#include "TRL/AttributeUniformInfo.h"
#include "TRL/AttributeVariable.h"
#include "TRL/UniformVariable.h"
#include "TRL/details/OpenGL/OpenGLCommonType.h"
#include "TRL/details/OpenGL/OpenGLShader.h"
#include "TRL/details/OpenGL/OpenGLTexture.h"


namespace TRL
{

namespace details
{


class OpenGLProgram
{
public:
    bool Init(OpenGLShader& vertShader, OpenGLShader& fragShader)
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
                // TODOL
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

    bool IsLinkSucc() const { return m_LinkedSucc; }
    const String& GetLinkErrorInfo() const { return m_LinkLog; }

    const AttributeUniformInfo& GetAttributeUniformInfo() const { return m_Infos; }

    void Destory()
    {
        glDeleteProgram(m_ProgramInner);
    }

    GLuint GetInnerName() const
    {
        return m_ProgramInner;
    }


private:
    void _PrepareUniformInfos(OpenGLShader& vertShader, OpenGLShader& fragShader)
    {
        if (vertShader.IsGeneratedByTRLShader())
        {
            // TODOM
        }
        else
        {
            GLint uniformNum, maxUniformNameLength;
            glGetProgramiv(m_ProgramInner, GL_ACTIVE_UNIFORMS, &uniformNum);
            glGetProgramiv(m_ProgramInner, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLength);

            char name[1024]; // TODOL

            for (int index = 0; index < uniformNum; ++index)
            {
                GLint size;
                GLenum type;
                GLint location;

                glGetActiveUniform(m_ProgramInner, index, maxUniformNameLength, NULL, &size, &type, name);
                location = glGetUniformLocation(m_ProgramInner, name);
                m_Infos.PushUniform(UniformVariable(name, location, (GpuDataType)type, size));
            }
        }
    }

    void _PrepareAttributeInfos(OpenGLShader& vertShader, OpenGLShader& fragShader)
    {
        if (vertShader.IsGeneratedByTRLShader())
        {
            // TODOM
        }
        else
        {
            GLint attributeNum, maxAttributeNameLength;
            glGetProgramiv(m_ProgramInner, GL_ACTIVE_ATTRIBUTES, &attributeNum);
            glGetProgramiv(m_ProgramInner, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttributeNameLength);

            char name[1024]; // TODOL

            for (int index = 0; index < attributeNum; ++index)
            {
                GLint size;
                GLenum type;
                GLint location; // layout

                glGetActiveAttrib(m_ProgramInner, index, maxAttributeNameLength, NULL, &size, &type, name);
                location = glGetAttribLocation(m_ProgramInner, name);
                m_Infos.PushAttribute(AttributeVariable(name, location, (GpuDataType)type, size));
            }
        }
    }


private:
    GLuint m_ProgramInner;
    bool m_LinkedSucc;
    ToyUtility::String m_LinkLog;
    AttributeUniformInfo m_Infos;
};


} // end of namespace details

} // end of namespace TRL