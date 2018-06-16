#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/Container/List.h"
#include "TRL/details/VGI/Adapter.h"
#include "TRL/details/VGI/Monitor.h"
#include "TRL/details/VGI/Window.h"

namespace TRL
{

namespace details
{


using ToyUtility::int8;
using ToyUtility::int16;
using ToyUtility::int32;
using ToyUtility::int64;
using ToyUtility::uint8;
using ToyUtility::uint16;
using ToyUtility::uint32;
using ToyUtility::uint64;


// Virtual Graphics Infrastructure
class VGI
{
public:
    virtual ~VGI() = default;


public:
    virtual void StartUp() = 0;
    virtual void ShutDown() = 0;

    virtual const ToyUtility::List<ToyUtility::SPtr<Adapter>>& GetAdapters() = 0;
    
    virtual Window* WindowCreate(const WINDOW_CREATE_DESC & desc) = 0;
    virtual const ToyUtility::List<Window*>& GetWindows() const = 0;
    virtual void WindowDestory(Window* window) = 0;
    virtual Window* GetMainWindow() = 0;
    virtual void SetMainWindow(Window* window) = 0;
    virtual bool IsMainWindow(Window* window) = 0;
    virtual void WindowPresent(Window* window, uint32 syncInterval) = 0;

    virtual void SetViewport(uint32 topLeftX, uint32 topLeftY, uint32 width, uint32 height) = 0;
};


} // end of namespace details

} // end of namespace TRL