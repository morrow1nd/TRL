#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/DataClasses.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/details/VGI/Window.h"
#include "TRL/details/VGI/WinDX/WinDXCommon.h"


namespace TRL
{

namespace details
{


class WinDXWindow : public Window
{
public:
    WinDXWindow(const WinDXContext& context)
        :
        m_Context(context),
        m_Windowed(true)
    {}


public:
    virtual bool Init(const WINDOW_CREATE_DESC& desc) override;
    virtual void SetTitle(const ToyUtility::String & title) override;
    virtual void SetSize(ToyUtility::uint32 width, ToyUtility::uint32 height) override;
    virtual void GetSize(ToyUtility::uint32 * width, ToyUtility::uint32 * height) const override;
    virtual void SetPosition(ToyUtility::int32 x, ToyUtility::int32 y) override;
    virtual void GetPosition(ToyUtility::int32 * x, ToyUtility::int32 * y) const override;
    virtual void SetVisible(bool visible) override;
    virtual void Focus() override;
    virtual bool IsWindowed() override;
    virtual void Present(uint32 syncInterval) override;
    virtual void Destory() override;


private:
    const WinDXContext& m_Context;

    HWND                                m_HWND;
    IDXGISwapChain*                     m_SwapChain;
    ID3D11Texture2D*                    m_BackBuffer;
    ID3D11RenderTargetView*             m_RenderTargetView;
    ID3D11Texture2D*                    m_DepthStencil;
    ID3D11DepthStencilView*             m_DepthStencilView;

    bool m_Windowed;
};


} // end of namespace details

} // end of namespace TRL