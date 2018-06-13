#pragma once

#include "TRLConfig.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Memory/SmartPtr.h"
#include "ToyUtility/Math/Matrix4.h"
#include "TRL/CommonType.h"
#include "TRL/GpuBuffer.h"
#include "TRL/GpuShader.h"


namespace TRL
{


class GpuProgram;
class AttributeData;


enum class TRLNativeApi
{
    Unknown = 0,

    OpenGL = TRL_OPENGL, // OpenGL 3.3
    OpenGLES = TRL_OPENGLES, // OpenGL ES 3.0
    DirectX11 = TRL_DX11,
};


class RenderAPI
{
public:
    static int GetGpuDataTypeSize(GpuDataType dataType);


public:
    TRLNativeApi GetUsedNativeApi() const;

    GpuBuffer CreateGpuBuffer();

    GpuShader CreateGpuShader();


    void ActiveGpuProgram(const GpuProgram& program);
    bool IsActiveGpuProgram(const GpuProgram& program);

    void DrawIndices(GpuPrimitiveType mode, const AttributeData& attributeData, int offset = 0);

    // Contain a default matrix into a matrix suitable for use by this specific render system.
    void ConvertProjectionMatrix(const ToyUtility::Matrix4& matrix, ToyUtility::Matrix4& dest);


private:
    GpuProgramInner m_ActiveGpuProgram;
};


} // end of namespace TRL