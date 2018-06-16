#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DesignPattern/IUncopyable.h"
#include "ToyUtility/Container/List.h"
#include "TRL/DataClasses.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/details/VGI/Monitor.h"


namespace TRL
{

namespace details
{


class Adapter : ToyUtility::IUncopyable, public ContainHandle<AdapterHandle>
{
public:
    Adapter()
    {
        static int adapterId = 0;
        SetHandle(AdapterHandle(++adapterId));
    }

    virtual ~Adapter() = default;


public:
    virtual bool IsDefaultAdapter() const = 0;
    virtual void GetDesc(AdapterDesc& desc) const = 0;
    virtual const ToyUtility::List<Monitor*>& GetMonitors() const = 0;
};


} // end of namespace details

} // end of namespace TRL