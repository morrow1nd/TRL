#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuBuffer
{
public:
    // Create multi buffer in one call
    static ToyUtility::List<ToyUtility::SPtr<GpuBuffer>> CreateBuffers(int number);

public:
    GpuBuffer()
        :
        m_BufferObject(0),
        m_BufferType(GPU_BUFFER_TYPE_INIT)
    { }


public:
    void Init();
    void Bind(GpuBufferType type);
    void Bind() const;
    void UploadData(void* data, int size, GpuBufferDataType dataType) const;
    void UploadSubData(void* data, int size, int offset) const;
    GpuBufferType GetBufferType() const;
    void CleanData() const;
    void Destory();


private:
    GpuBufferObjectInner m_BufferObject;
    GpuBufferType m_BufferType;
};


} // end of namespace TRL