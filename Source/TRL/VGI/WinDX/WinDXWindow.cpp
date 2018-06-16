#include "TRL/details/VGI/WinDX/WinDXWindow.h"


namespace TRL
{

namespace details
{


bool WinDXWindow::Init(const WINDOW_CREATE_DESC & desc)
{
    static int WindowClassName = 1;
    ToyUtility::String className = "WindowsWindowClass" + std::to_string(WindowClassName++);

    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = m_Context.WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_Context.ProgramInstance;
    wcex.hIcon = 0; // TODOL: icon
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = className.c_str();
    wcex.hIconSm = 0; // TODOL: small icon
    if (!RegisterClassEx(&wcex))
        return false;

    // Create window
    RECT rc = {desc.WindowRect.x, desc.WindowRect.y, desc.WindowRect.width, desc.WindowRect.height};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_HWND = CreateWindow(className.c_str(), desc.Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, m_Context.ProgramInstance,
        NULL);
    if (!m_HWND)
        return false;

    // TODOH: ShowWindow(g_hWnd, nCmdShow);

    // Create SwapChain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = desc.BufferCount;
    sd.BufferDesc.Width = desc.BufferDesc.Width;
    sd.BufferDesc.Height = desc.BufferDesc.Height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = desc.BufferDesc.RefreshRate.Numerator();
    sd.BufferDesc.RefreshRate.Denominator = desc.BufferDesc.RefreshRate.Denominator();
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_HWND;
    sd.SampleDesc.Count = desc.SampleDesc.Count;
    sd.SampleDesc.Quality = desc.SampleDesc.Quality;
    sd.Windowed = desc.Windowed ? TRUE : FALSE;
    m_Windowed = desc.Windowed;

    m_SwapChain = NULL;
    HRESULT hr = m_Context.Factory->CreateSwapChain(m_Context.Device, &sd, &m_SwapChain);
    if (FAILED(hr))
    {
        // TODOH
    }

    // Create a render target view
    m_BackBuffer = NULL;
    hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_BackBuffer);
    if (FAILED(hr))
        return false;

    m_RenderTargetView = NULL;
    hr = m_Context.Device->CreateRenderTargetView(m_BackBuffer, NULL, &m_RenderTargetView);
    m_BackBuffer->Release();
    if (FAILED(hr))
        return false;

    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = desc.BufferDesc.Width;
    descDepth.Height = desc.BufferDesc.Height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = m_Context.Device->CreateTexture2D(&descDepth, NULL, &m_DepthStencil);
    if (FAILED(hr))
        return false;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = m_Context.Device->CreateDepthStencilView(m_DepthStencil, &descDSV, &m_DepthStencilView);
    if (FAILED(hr))
        return false;

    m_Context.DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)desc.BufferDesc.Width;
    vp.Height = (FLOAT)desc.BufferDesc.Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_Context.DeviceContext->RSSetViewports(1, &vp);

    return true;
}

void WinDXWindow::SetTitle(const ToyUtility::String & title)
{
    SetWindowText(m_HWND, title.c_str());
}

void WinDXWindow::SetSize(ToyUtility::uint32 width, ToyUtility::uint32 height)
{
    if (IsWindowed())
    {
        // TODOM: copied from glfw:win32_window.c:L1133
        RECT rect = {0, 0, width, height};
        AdjustWindowRectEx(&rect, WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            FALSE, WS_EX_APPWINDOW);
        SetWindowPos(m_HWND, HWND_TOP,
            0, 0, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
    }
}

void WinDXWindow::GetSize(ToyUtility::uint32 * width, ToyUtility::uint32 * height) const
{
    RECT area;
    GetClientRect(m_HWND, &area);

    if(width)
        *width = area.right;
    if(height)
        *height = area.bottom;
}

void WinDXWindow::SetPosition(ToyUtility::int32 x, ToyUtility::int32 y)
{
    // TODOM: copied from glfw:win32_window.c:L1115
    RECT rect = {x, y, x, y};
    AdjustWindowRectEx(&rect, WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        FALSE, WS_EX_APPWINDOW);
    SetWindowPos(m_HWND, NULL, rect.left, rect.top, 0, 0,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

void WinDXWindow::GetPosition(ToyUtility::int32 * x, ToyUtility::int32 * y) const
{
    POINT pos = {0, 0};
    ClientToScreen(m_HWND, &pos);

    if (x)
        *x = pos.x;
    if (y)
        *y = pos.y;
}

void WinDXWindow::SetVisible(bool visible)
{
    ShowWindow(m_HWND, visible ? SW_SHOW : SW_HIDE);
}

void WinDXWindow::Focus()
{
    BringWindowToTop(m_HWND);
    SetForegroundWindow(m_HWND);
    SetFocus(m_HWND);
}

bool WinDXWindow::IsWindowed()
{
    return m_Windowed;
}

void WinDXWindow::Present(uint32 syncInterval)
{
    m_SwapChain->Present(syncInterval, 0);
}

void WinDXWindow::Destory()
{
}


} // end of namespace details

} // end of namespace TRL