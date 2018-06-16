#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "TRLConfig.h"
#include "TRL/TRLCommonType.h"


namespace TRL
{


class GpuObjectHandle
{
public:
    GpuObjectHandle()
        : m_Id(0)
    {}

    GpuObjectHandle(int id)
        : m_Id(id)
    {}

    int Id() const
    {
        return m_Id;
    }

    bool operator==(const GpuObjectHandle& rhs) const
    {
        return m_Id == rhs.m_Id;
    }

    bool operator!=(const GpuObjectHandle& rhs) const
    {
        return !(rhs == *this);
    }


private:
    int m_Id;
};

struct GpuBufferHandle : public GpuObjectHandle
{
    GpuBufferHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};

struct GpuProgramHandle : public GpuObjectHandle
{
    GpuProgramHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};

struct GpuShaderHandle : public GpuObjectHandle
{
    GpuShaderHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};

class GpuTextureHandle : public GpuObjectHandle
{
public:
    GpuTextureHandle()
        :
        m_TextureType(GPU_TEXTURE_TYPE_INIT)
    {}

    GpuTextureHandle(int id)
        :
        GpuObjectHandle(id),
        m_TextureType(GPU_TEXTURE_TYPE_INIT)
    {}

    GpuTextureType TextureType() const { return m_TextureType; }


protected:
    GpuTextureType m_TextureType;
};

class GpuTexture2DHandle : public GpuTextureHandle
{
public:
    GpuTexture2DHandle()
    {
        m_TextureType = GPU_TEXTURE_2D;
    }

    GpuTexture2DHandle(int id)
        :
        GpuTextureHandle(id)
    {
        m_TextureType = GPU_TEXTURE_2D;
    }

    GpuTexture2DHandle(const GpuTextureHandle& handle)
        :
        GpuTextureHandle(handle.Id())
    {
        m_TextureType = GPU_TEXTURE_2D;
    }
};

struct GpuAttributeDataHandle : public GpuObjectHandle
{
    GpuAttributeDataHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};

struct WindowHandle : public GpuObjectHandle
{
    WindowHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};

struct MonitorHandle : public GpuObjectHandle
{
    MonitorHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};

struct AdapterHandle : public GpuObjectHandle
{
    AdapterHandle(int id)
        :
        GpuObjectHandle(id)
    {}
};


template<typename H, typename T, bool ReuseId = true>
class IndexedContainer
{
public:
    IndexedContainer()
    {
        m_List.push_back(T()); // Unused Object(0)
    }


    T& Get(H handle) { return m_List[handle.Id()]; }

    const T& Get(H handle) const { return m_List[handle.Id()]; }

    void Destory(H handle)
    {
        m_UnusedIndices.push_back(handle.Id());
        m_List[handle.Id()] = T(); // Clean it
    }

    H New()
    {
        if (ReuseId)
        {
            if (m_UnusedIndices.empty())
            {
                m_List.push_back(T());
                return H(m_List.size() - 1);
            }
            else
            {
                auto ret = m_UnusedIndices.back();
                m_UnusedIndices.pop_back();
                return H(ret);
            }
        }
        else
        {
            m_List.push_back(T());
            return H(m_List.size() - 1);
        }
    }


private:
    ToyUtility::List<T> m_List;

    ToyUtility::List<int> m_UnusedIndices;
};

template<typename HandleType>
class ContainHandle
{
public:
    ContainHandle()
        :
        m_Handle(0)
    {}

    ContainHandle(ToyUtility::uint32 id)
        :
        m_Handle(id)
    {}


    HandleType GetHandle() const
    {
        return m_Handle;
    }

    void SetHandle(HandleType handle)
    {
        m_Handle = handle;
    }


private:
    HandleType m_Handle;
};


} // end of namespace TRL