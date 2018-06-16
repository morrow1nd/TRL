#include "TRL/details/VGI/WinDX/WinDXVGI.h"

#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>
#include <d3dcompiler.h>

#include "TRL/details/VGI/WinDX/WinDXAdapter.h"


namespace TRL
{

namespace details
{


void WinDXVGI::SetInstance(HINSTANCE hInstance)
{
    m_Context.ProgramInstance = hInstance;
}

void WinDXVGI::SetWndProc(WNDPROC wndProc)
{
    m_Context.WndProc = wndProc;
}

void WinDXVGI::StartUp()
{
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_Context.Factory);
    if (FAILED(hr))
    {
        // TODOH
        return;
    }

    _InitAdapters();

    _CreateDevice();
}

void WinDXVGI::ShutDown()
{
    _DestoryDevice();

    // TODOH: release IDXGIAdapter

    if (m_Context.Factory)
    {
        m_Context.Factory->Release();
        m_Context.Factory = nullptr;
    }
}

const ToyUtility::List<ToyUtility::SPtr<Adapter>>& WinDXVGI::GetAdapters()
{
    _RescanAdapters();
    return m_Adapters;
}

Window * WinDXVGI::WindowCreate(const WINDOW_CREATE_DESC & desc)
{
    ToyUtility::SPtr<WinDXWindow> window = ToyUtility::SPtr<WinDXWindow>(new WinDXWindow(m_Context));

    if (window->Init(desc))
    {
        m_Windows.push_back(window);
        return window.get();
    }

    return nullptr;
}

const ToyUtility::List<Window*>& WinDXVGI::GetWindows() const
{
    m_TemWindows.clear();
    for each(auto win in m_Windows)
    {
        m_TemWindows.push_back(win.get());
    }
    return m_TemWindows;
}

void WinDXVGI::WindowDestory(Window * window)
{
    ToyUtility::SPtr<WinDXWindow> target;

    for (auto i = m_Windows.begin(), end = m_Windows.end();
        i != end;
        ++i)
    {
        if ((*i)->GetHandle() == window->GetHandle())
        {
            target = *i;
            m_Windows.erase(i);
            break;
        }
    }

    target->Destory();
}

Window * WinDXVGI::GetMainWindow()
{
    return m_MainWindow.get();
}

void WinDXVGI::SetMainWindow(Window * window)
{
    m_MainWindow.reset(dynamic_cast<WinDXWindow*>(window));
}

bool WinDXVGI::IsMainWindow(Window * window)
{
    if(window == nullptr)
        return false;

    if(m_MainWindow == nullptr)
        return false;

    return window->GetHandle() == m_MainWindow->GetHandle();
}

void WinDXVGI::WindowPresent(Window * window, uint32 syncInterval)
{
    window->Present(syncInterval);
}

void WinDXVGI::SetViewport(uint32 topLeftX, uint32 topLeftY, uint32 width, uint32 height)
{
    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = topLeftX;
    viewport.TopLeftY = topLeftY;
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;
    m_Context.DeviceContext->RSSetViewports(1, &viewport);
}

void WinDXVGI::_CreateDevice()
{
    HRESULT hr;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    //IDXGIAdapter* defaultAdapter = dynamic_cast<WinDXAdapter*>(m_Adapters.front().get())->GetDXGIAdapter();
    hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
        D3D11_SDK_VERSION, &m_Context.Device, &m_FeatureLevel, &m_Context.DeviceContext);
    if (FAILED(hr))
    {
        // TODOH
    }
}

void WinDXVGI::_DestoryDevice()
{
    if (m_Context.DeviceContext)
    {
        m_Context.DeviceContext->ClearState();
    }

    if (m_Context.DeviceContext)
    {
        m_Context.DeviceContext->Release();
        m_Context.DeviceContext = nullptr;
    }

    if (m_Context.Device)
    {
        m_Context.Device->Release();
        m_Context.Device = nullptr;
    }
}

void WinDXVGI::_InitAdapters()
{
    IDXGIAdapter * pAdapter;
    for (UINT i = 0;
        m_Context.Factory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND;
        ++i)
    {
        auto adapter = ToyUtility::SPtr<WinDXAdapter>(new WinDXAdapter());
        
        adapter->Init(pAdapter);

        m_Adapters.push_back(adapter);
    }
}

// TODOM
void WinDXVGI::_RescanAdapters()
{
    //ToyUtility::List<IDXGIAdapter*> rawAdapters;

    //IDXGIAdapter * pAdapter;
    //for (UINT i = 0;
    //    m_Context.Factory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND;
    //    ++i)
    //{
    //    rawAdapters.push_back(pAdapter);
    //}

    //if (rawAdapters.size() == m_Adapters.size())
    //{
    //}
}

} // end of namespace details

} // end of namespace TRL