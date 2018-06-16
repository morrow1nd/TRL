#pragma once

#include <dxgi.h>
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/DataClasses.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/details/VGI/Adapter.h"


namespace TRL
{

namespace details
{


class WinDXAdapter : public Adapter
{
public:
    void Init(IDXGIAdapter* adapter){ }
    IDXGIAdapter* GetDXGIAdapter(){return nullptr; }

    virtual bool IsDefaultAdapter() const override;
    virtual void GetDesc(AdapterDesc & desc) const override;
    virtual const ToyUtility::List<Monitor*>& GetMonitors() const override;
};


} // end of namespace details

} // end of namespace TRL