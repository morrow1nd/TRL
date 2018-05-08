#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/Math/Matrix4.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuProgram;
class AttributeData;


class RenderAPI
{
public:
    static int GetGpuDataTypeSize(GpuDataType dataType);


public:
    void ActiveGpuProgram(const GpuProgram& program);
    bool IsActiveGpuProgram(const GpuProgram& program);

    void DrawIndices(GpuPrimitiveType mode, const AttributeData& attributeData, int offset = 0);

    // Contain a default matrix into a matrix suitable for use by this specific render system.
    void ConvertProjectionMatrix(const ToyUtility::Matrix4& matrix, ToyUtility::Matrix4& dest);


private:
    GpuProgramInner m_ActiveGpuProgram;
};


} // end of namespace TRL