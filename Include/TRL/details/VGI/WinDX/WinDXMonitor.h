#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/DataClasses.h"
#include "TRL/GpuObjectHandles.h"
#include "TRL/details/VGI/Monitor.h"


namespace TRL
{

namespace details
{


class WinDXMonitor : public Monitor
{
    virtual void GetDesc(MonitorDesc & desc) const override;
};


} // end of namespace details

} // end of namespace TRL