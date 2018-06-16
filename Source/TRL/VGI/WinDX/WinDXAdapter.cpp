#include "TRL/details/VGI/WinDX/WinDXAdapter.h"


namespace TRL
{

namespace details
{




bool WinDXAdapter::IsDefaultAdapter() const
{
    return false;
}

void WinDXAdapter::GetDesc(AdapterDesc & desc) const
{
}

const ToyUtility::List<Monitor*>& WinDXAdapter::GetMonitors() const
{
    // TODO: insert return statement here
    return ToyUtility::List<Monitor*>();
}

} // end of namespace details

} // end of namespace TRL