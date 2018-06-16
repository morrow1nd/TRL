#pragma once

#include <dxgi.h>

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "TRL/DataClasses.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/details/VGI/VGI.h"
#include "TRL/details/VGI/WinDX/WinDXAdapter.h"
#include "TRL/details/VGI/WinDX/WinDXWindow.h"
#include "TRL/details/VGI/WinDX/WinDXCommon.h"


namespace TRL
{

namespace details
{


class WinDXVGI : public VGI
{
public:
    WinDXVGI()
        :
        m_FeatureLevel(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
    {}


private:
    WinDXContext m_Context;

    ToyUtility::List<ToyUtility::SPtr<Adapter>> m_Adapters;
    ToyUtility::List<ToyUtility::SPtr<WinDXWindow>> m_Windows;
    mutable ToyUtility::List<Window*> m_TemWindows;

    D3D_FEATURE_LEVEL m_FeatureLevel;

    ToyUtility::SPtr<WinDXWindow> m_MainWindow;


public:
    void SetInstance(HINSTANCE hInstance);
    void SetWndProc(WNDPROC wndProc);


public:
    virtual void StartUp() override;
    virtual void ShutDown() override;
    virtual const ToyUtility::List<ToyUtility::SPtr<Adapter>>& GetAdapters() override;
    virtual Window * WindowCreate(const WINDOW_CREATE_DESC & desc) override;
    virtual const ToyUtility::List<Window*>& GetWindows() const override;
    virtual void WindowDestory(Window * window) override;
    virtual Window * GetMainWindow() override;
    virtual void SetMainWindow(Window * window) override;
    virtual bool IsMainWindow(Window * window) override;
    virtual void WindowPresent(Window * window, uint32 syncInterval) override;
    virtual void SetViewport(uint32 topLeftX, uint32 topLeftY, uint32 width, uint32 height) override;


private:
    void _CreateDevice();
    void _DestoryDevice();
    void _InitAdapters();
    void _RescanAdapters();
};


} // end of namespace details

} // end of namespace TRL