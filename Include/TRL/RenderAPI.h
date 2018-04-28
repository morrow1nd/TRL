#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuProgram;
class AttributeData;


class RenderAPI
{
public:
    void ActiveGpuProgram(const GpuProgram& program);
    bool IsActiveGpuProgram(const GpuProgram& program);

    void DrawIndices(GpuPrimitiveType mode, const AttributeData& attributeData, int offset);

private:
    GpuProgramInner m_ActiveGpuProgram;
};


} // end of namespace TRL