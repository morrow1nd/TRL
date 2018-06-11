#include "TRL/GpuBuffer.h"


namespace TRL
{


void GpuBuffer::Init()
{
    glGenBuffers(1, &m_BufferObject);
}

void GpuBuffer::Bind(GpuBufferType bufferType)
{
    glBindBuffer(bufferType, m_BufferObject);
    m_BufferType = bufferType;
}

void GpuBuffer::Bind() const
{
    glBindBuffer(m_BufferType, m_BufferObject);
}

void GpuBuffer::UploadData(void * data, int size, GpuBufferDataType dataType) const
{
    glBufferData(m_BufferType, size, data, dataType);
}

void GpuBuffer::UploadSubData(void * data, int size, int offset) const
{
    glBufferSubData(m_BufferType, offset, size, data);
}

GpuBufferType GpuBuffer::GetBufferType() const
{
    return m_BufferType;
}

void GpuBuffer::CleanData() const
{
    glBufferData(m_BufferType, 0, NULL, 0); // todo: check this usage
}

void GpuBuffer::Destory()
{
    glDeleteBuffers(1, &m_BufferObject);
}




} // end of namespace TRL