#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DesignPattern/IUncopyable.h"
#include "TRL/DataClasses.h"


namespace TRL
{

namespace details
{


class Monitor : ToyUtility::IUncopyable, public ContainHandle<MonitorHandle>
{
public:
    Monitor()
    {
        static int adapterId = 0;
        SetHandle(MonitorHandle(++adapterId));
    }

    virtual ~Monitor() = default;


public:
    virtual void GetDesc(MonitorDesc& desc) const = 0;
};


} // end of namespace details

} // end of namespace TRL