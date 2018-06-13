#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/OpenGL/OpenGLCommonType.h"


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
    void Init()
    {
        glGenBuffers(1, &m_BufferObject);
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

    void UploadData(const void* data, int size, GpuBufferDataType dataType)
    {
        glBufferData(TRL_GL_NATIVE(m_BufferType), size, data, dataType);
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
    GLuint m_BufferObject;
    GpuBufferType m_BufferType;
    int m_DataSize;
};


} // end of namespace details

} // end of namespace TRL