#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"


namespace TRL
{


struct AdapterDesc
{
    ToyUtility::String Description; // A string that contains the adapter description
    ToyUtility::uint32 VendorId; // The PCI ID of the hardware vendor. PCI: http://pci-ids.ucw.cz/
    ToyUtility::uint32 DeviceId; // The PCI ID of the hardware device
    ToyUtility::uint32 SubSysId; // The PCI ID of the sub system
    ToyUtility::uint32 Revision; // The PCI ID of the revision number of the adapter
    ToyUtility::uint64 DedicatedVideoMemory; // The number of bytes of dedicated video memory that are not shared with the CPU
    ToyUtility::uint64 DedicatedSystemMemory; // The number of bytes of dedicated system memory that are not shared with the GPU. This memory is allocated from available system memory at boot time
    ToyUtility::uint64 SharedSystemMemory; // The number of bytes of shared system memory. This is the maximum value of system memory that may be consumed by the adapter during operation. Any incidental memory consumed by the driver as it manages and uses video memory is additional
    ToyUtility::uint64 AdapterLuid; // A unique value that identifies the adapter
};


} // end of namespace TRL