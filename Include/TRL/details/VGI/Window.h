#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DesignPattern/IUncopyable.h"
#include "ToyUtility/String/String.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/DataClasses.h"


namespace TRL
{

namespace details
{


class Window : ToyUtility::IUncopyable, public ContainHandle<WindowHandle>
{
public:
    Window()
    {
        static int adapterId = 0;
        SetHandle(WindowHandle(++adapterId));
    }

    virtual ~Window() = default;


public:
    virtual bool Init(const WINDOW_CREATE_DESC& desc) = 0;
    virtual void Destory() = 0;
    virtual void SetTitle(const ToyUtility::String& title) = 0;
    virtual void SetSize(ToyUtility::uint32 width, ToyUtility::uint32 height) = 0;
    virtual void GetSize(ToyUtility::uint32* width, ToyUtility::uint32* height) const = 0;
    virtual void SetPosition(ToyUtility::int32 x, ToyUtility::int32 y) = 0;
    virtual void GetPosition(ToyUtility::int32* x, ToyUtility::int32* y) const = 0;
    virtual void SetVisible(bool visible) = 0;
    virtual void Focus() = 0;
    virtual bool IsWindowed() = 0;
    virtual void Present(uint32 syncInterval) = 0;
};


} // end of namespace details

} // end of namespace TRL