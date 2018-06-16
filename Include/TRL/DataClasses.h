#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Math/Rational.h"
#include "ToyUtility/Math/Rect2I.h"


namespace TRL
{


struct SampleDesc
{
    static SampleDesc NoMultiSampling;

    SampleDesc()
        :
        Count(1),
        Quality(0)
    {}

    SampleDesc(ToyUtility::uint32 count, ToyUtility::uint32 quality)
        :
        Count(count),
        Quality(quality)
    {}


    ToyUtility::uint32 Count; // The number of multisamples per pixel
    ToyUtility::uint32 Quality; // The image quality level. The higher the quality, the lower the performance
};

struct ModeDesc
{
    ModeDesc()
        :
        Width(0),
        Height(0)
    {}


    ToyUtility::uint32 Width; // resolution width
    ToyUtility::uint32 Height; // resolution height
    ToyUtility::Rational RefreshRate; // refresh rate in hertz
    // TODOH: format, scanlineOrdering, scaling
};

enum class MonitorRotationType
{
    Unspecified,
    Identity,
    Rotate90,
    Rotate180,
    Rotate270,
};

struct MonitorDesc
{
    MonitorDesc()
        :
        DeviceName("-Unknown-"),
        AttachedToDesktop(true),
        Rotation(MonitorRotationType::Unspecified)
    {}


    ToyUtility::String DeviceName;
    ToyUtility::Rect2I DesktopCoordinates; // containing the bounds of the output in desktop coordinates
    bool AttachedToDesktop;
    MonitorRotationType Rotation;
};

struct AdapterDesc
{
    AdapterDesc()
        :
        VendorId(0),
        DeviceId(0),
        SubSysId(0),
        Revision(0),
        DedicatedVideoMemory(0),
        DedicatedSystemMemory(0),
        SharedSystemMemory(0),
        AdapterLUID(0)
    {}


    ToyUtility::String Description; // A string that contains the adapter description
    ToyUtility::uint32 VendorId; // The PCI ID of the hardware vendor. PCI: http://pci-ids.ucw.cz/
    ToyUtility::uint32 DeviceId; // The PCI ID of the hardware device
    ToyUtility::uint32 SubSysId; // The PCI ID of the sub system
    ToyUtility::uint32 Revision; // The PCI ID of the revision number of the adapter
    ToyUtility::uint64 DedicatedVideoMemory; // The number of bytes of dedicated video memory that are not shared with the CPU
    ToyUtility::uint64 DedicatedSystemMemory; // The number of bytes of dedicated system memory that are not shared with the GPU. This memory is allocated from available system memory at boot time
    ToyUtility::uint64 SharedSystemMemory; // The number of bytes of shared system memory. This is the maximum value of system memory that may be consumed by the adapter during operation. Any incidental memory consumed by the driver as it manages and uses video memory is additional
    ToyUtility::uint64 AdapterLUID; // A unique value that identifies the adapter
};

struct WINDOW_CREATE_DESC
{
    WINDOW_CREATE_DESC()
        :
        Title(""),
        Windowed(true),
        BufferCount(1)
    {}


    ToyUtility::String              Title;
    ToyUtility::Rect2I              WindowRect;

    bool                            Windowed; // Windowed mode
    ModeDesc                        BufferDesc; // Describing the backbuffer display mode
    SampleDesc                      SampleDesc; // describing multi-sampling 
    ToyUtility::uint32              BufferCount; // Back buffer count
};


} // end of namespace TRL