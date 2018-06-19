#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLCommonType.h"


namespace TRL
{

namespace details
{


class OpenGLBuffer
{
public:
    OpenGLBuffer()
        :
        m_BufferObject(0),
        m_BufferType(GPU_BUFFER_TYPE_INIT),
        m_DataSize(0)
    {
    }


public:
    void Init(const GPU_BUFFER_DESC& desc)
    {
        glGenBuffers(1, &m_BufferObject);
        auto bufferType = TRL_GL_NATIVE(desc.BufferType);
        glBindBuffer(bufferType, m_BufferObject);
        glBufferData(bufferType, desc.InitData.Size, desc.InitData.SysMem, _GetBufferDataType(desc.ModifyHint, desc.Access));

        m_BufferType = desc.BufferType;
        m_DataSize = desc.InitData.Size;
        m_Access = desc.Access;
        m_ModifyHint = desc.ModifyHint;
    }

    void Bind(GpuBufferType bufferType)
    {
        glBindBuffer(TRL_GL_NATIVE(bufferType), m_BufferObject);
        m_BufferType = bufferType;
    }

    void Bind() const
    {
        glBindBuffer(TRL_GL_NATIVE(m_BufferType), m_BufferObject);
    }

    void UploadData(const void* data, int size)
    {
        glBufferData(TRL_GL_NATIVE(m_BufferType), size, data, _GetBufferDataType(m_ModifyHint, m_Access));
        m_DataSize = size;
    }

    int GetDataSize() const { return m_DataSize; }

    void UploadSubData(const void* data, int size, int offset) const
    {
        glBufferSubData(TRL_GL_NATIVE(m_BufferType), offset, size, data);
    }

    GpuBufferType GetBufferType() const
    {
        return m_BufferType;
    }

    void CleanData() const
    {
        glBufferData(TRL_GL_NATIVE(m_BufferType), 0, NULL, 0); // todo: check this usage
    }

    void Destory()
    {
        glDeleteBuffers(1, &m_BufferObject);
    }


private:
    GLenum _GetBufferDataType(GpuBufferModifyHint modifyHint, GpuBufferAccessType access) const
    {
        static ToyUtility::List<ToyUtility::List<GLenum>> data =
        {
        {
            GL_STREAM_DRAW,
            GL_STREAM_DRAW,
            GL_STREAM_READ,
        },
        {
            GL_STATIC_DRAW,
            GL_STATIC_DRAW,
            GL_STATIC_READ,
        },
        {
            GL_DYNAMIC_DRAW,
            GL_DYNAMIC_DRAW,
            GL_DYNAMIC_READ,
        },
        };

        return data[(int)modifyHint][(int)access];
    }


private:
    GLuint m_BufferObject;
    GpuBufferType m_BufferType;
    int m_DataSize; // (in bytes)

    GpuBufferAccessType             m_Access;
    GpuBufferModifyHint             m_ModifyHint;
};


} // end of namespace details

} // end of namespace TRL