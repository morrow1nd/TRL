#pragma once

#include <dxgi.h>
#include <d3d11.h>

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/GpuObjectHandles.h"


namespace TRL
{

namespace details
{


struct WinDXContext
{
    WinDXContext()
        :
        Factory(nullptr),
        Device(nullptr),
        DeviceContext(nullptr),
        ProgramInstance(0),
        WndProc(nullptr)
    {}


    IDXGIFactory* Factory;
    ID3D11Device* Device;
    ID3D11DeviceContext* DeviceContext;

    HINSTANCE ProgramInstance;
    WNDPROC WndProc;
};


} // end of namespace details

} // end of namespace TRL