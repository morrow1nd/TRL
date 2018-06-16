#include "TRL/RenderAPI.h"

#include "ToyUtility/Random/UUID.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLRenderAPI.h"
#include "TRL/details/RenderAPIImpl/DX11/DX11RenderAPI.h"

#include "TRL/details/VGI/WinDX/WinDXVGI.h"


namespace TRL
{


int RenderAPI::GetGpuDataTypeSize(GpuDataType dataType)
{
    switch (dataType)
    {
    case GPU_BOOL:
        return sizeof(bool);
        break;
    case GPU_INT8:
        return sizeof(int8);
        break;
    case GPU_UINT8:
        return sizeof(uint8);
        break;
    case GPU_INT16:
        return sizeof(int16);
        break;
    case GPU_UINT16:
        return sizeof(uint16);
        break;
    case GPU_INT32:
        return sizeof(int32);
        break;
    case GPU_UINT32:
        return sizeof(uint32);
        break;
    case GPU_HALF_FLOAT:
        return sizeof(uint16);
        break;
    case GPU_FLOAT:
        return sizeof(float);
        break;
    case GPU_FLOAT_VEC2:
        return sizeof(float[2]);
        break;
    case GPU_FLOAT_VEC3:
        return sizeof(float[3]);
        break;
    case GPU_FLOAT_VEC4:
        return sizeof(float[4]);
        break;
    case GPU_INT32_VEC2:
        return sizeof(int32[2]);
        break;
    case GPU_INT32_VEC3:
        return sizeof(int32[3]);
        break;
    case GPU_INT32_VEC4:
        return sizeof(int32[4]);
        break;
    case GPU_UINT32_VEC2:
        return sizeof(uint32[2]);
        break;
    case GPU_UINT32_VEC3:
        return sizeof(uint32[3]);
        break;
    case GPU_UINT32_VEC4:
        return sizeof(uint32[4]);
        break;
    case GPU_BOOL_VEC2:
        return sizeof(bool[2]); // TODO: check this
        break;
    case GPU_BOOL_VEC3:
        return sizeof(bool[3]); // TODO: check this
        break;
    case GPU_BOOL_VEC4:
        return sizeof(bool[4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT2:
        return sizeof(float[2][2]);
        break;
    case GPU_FLOAT_MAT3:
        return sizeof(float[3][3]);
        break;
    case GPU_FLOAT_MAT4:
        return sizeof(float[4][4]);
        break;
    case GPU_FLOAT_MAT2x3:
        return sizeof(float[2][3]); // TODO: check this
        break;
    case GPU_FLOAT_MAT2x4:
        return sizeof(float[2][4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT3x2:
        return sizeof(float[3][2]); // TODO: check this
        break;
    case GPU_FLOAT_MAT3x4:
        return sizeof(float[3][4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT4x2:
        return sizeof(float[4][2]); // TODO: check this
        break;
    case GPU_FLOAT_MAT4x3:
        return sizeof(float[4][3]); // TODO: check this
        break;
    case GPU_SAMPLER_2D:
    case GPU_SAMPLER_3D:
    case GPU_SAMPLER_CUBE:
        return sizeof(ToyUtility::UUID);
        break;
    default:
        assert(false && ("RenderAPI::GetGpuDataTypeSize comes to default: " + dataType));
        break;
    }

    return 0;
}

ToyUtility::SPtr<RenderAPI> RenderAPI::CreateDefaultRenderAPI()
{
    return ToyUtility::SPtr<RenderAPI>(new TRL::details::OpenGLRenderAPI());
}

ToyUtility::SPtr<RenderAPI> RenderAPI::CreateRenderAPI(TRLNativeApiType type)
{
    switch (type)
    {
    case TRLNativeApiType::DX11:
        return ToyUtility::SPtr<RenderAPI>(new TRL::details::DX11RenderAPI());
        break;
    case TRLNativeApiType::OpenGL:
        return ToyUtility::SPtr<RenderAPI>(new TRL::details::OpenGLRenderAPI());
        break;
    case TRLNativeApiType::OpenGLES:

        break;
    }

    return ToyUtility::SPtr<RenderAPI>();
}


void RenderAPI::StartUp(HINSTANCE hInstance, WNDPROC wndProc)
{
    auto vgi = new details::WinDXVGI();
    vgi->SetInstance(hInstance); // TODOH
    vgi->SetWndProc(wndProc); // TODOH
    
    m_VGI.reset(vgi);
    m_VGI->StartUp();
}

void RenderAPI::ShutDown()
{
    m_VGI->ShutDown();
}

AdapterHandle RenderAPI::GetDefaultAdapter()
{
    // TODOM
    assert(m_VGI->GetAdapters().size() > 0);

    return m_VGI->GetAdapters().front()->GetHandle();
}

const List<AdapterHandle>& RenderAPI::GetAdapters()
{
    auto adapters = m_VGI->GetAdapters();
    m_AdapterHandles.clear();
    for each(auto adapterp in adapters)
    {
        m_AdapterHandles.push_back(adapterp->GetHandle());
    }
    return m_AdapterHandles;
}

bool RenderAPI::AdapterGetDesc(AdapterHandle adapter, AdapterDesc & desc)
{
    auto adapters = m_VGI->GetAdapters();
    for each(auto adapterp in adapters)
    {
        if (adapter == adapterp->GetHandle())
        {
            adapterp->GetDesc(desc);
            return true;
        }
    }

    return false;
}

List<MonitorHandle> RenderAPI::AdapterGetMonitors(AdapterHandle adapter)
{
    auto adapters = m_VGI->GetAdapters();
    for each(auto adapterp in adapters)
    {
        if (adapter == adapterp->GetHandle())
        {
            auto monitors = adapterp->GetMonitors();
            List<MonitorHandle> result;
            for each(auto monitor in monitors)
            {
                result.push_back(monitor->GetHandle());
            }
            return result;
        }
    }

    return List<MonitorHandle>();
}

void RenderAPI::MonitorGetDesc(MonitorHandle monitor, MonitorDesc & desc)
{
    for each(auto adapterp in m_VGI->GetAdapters())
    {
        for each(auto monitorp in adapterp->GetMonitors())
        {
            if (monitor == monitorp->GetHandle())
            {
                monitorp->GetDesc(desc);
                return;
            }
        }
    }
}

WindowHandle RenderAPI::WindowCreate(const WINDOW_CREATE_DESC & desc)
{
    return m_VGI->WindowCreate(desc)->GetHandle();
}

void RenderAPI::WindowDestory(WindowHandle window)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            m_VGI->WindowDestory(windowp);
            return;
        }
    }
}

void RenderAPI::WindowSetMain(WindowHandle window)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            m_VGI->SetMainWindow(windowp);
            return;
        }
    }
}

WindowHandle RenderAPI::WindowGetMain() const
{
    return m_VGI->GetMainWindow()->GetHandle();
}

void RenderAPI::WindowSetTitle(WindowHandle window, const String & title)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->SetTitle(title);
            return;
        }
    }
}

void RenderAPI::WindowSetSize(WindowHandle window, uint32 width, uint32 height)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->SetSize(width, height);
            return;
        }
    }
}

void RenderAPI::WindowGetSize(WindowHandle window, uint32 * width, uint32 * height) const
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->GetSize(width, height);
            return;
        }
    }
}

void RenderAPI::WindowSetPosition(WindowHandle window, int32 x, int32 y)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->SetPosition(x, y);
            return;
        }
    }
}

void RenderAPI::WindowGetPosition(WindowHandle window, int32 * x, int32 * y)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->GetPosition(x, y);
            return;
        }
    }
}

void RenderAPI::WindowSetVisible(WindowHandle window, bool visible)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->SetVisible(visible);
            return;
        }
    }
}

void RenderAPI::WindowFocus(WindowHandle window)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            windowp->Focus();
            return;
        }
    }
}

void RenderAPI::WindowPresent(WindowHandle window, uint32 syncInterval)
{
    for each(auto windowp in m_VGI->GetWindows())
    {
        if (windowp->GetHandle() == window)
        {
            m_VGI->WindowPresent(windowp, syncInterval);
            return;
        }
    }
}

void RenderAPI::SetViewport(uint32 topLeftX, uint32 topLeftY, uint32 width, uint32 height)
{
    m_VGI->SetViewport(topLeftX, topLeftY, width, height);
}

} // end of namespace TRL