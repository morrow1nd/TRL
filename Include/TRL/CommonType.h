#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRLConfig.h"


namespace TRL
{


using ToyUtility::int8;
using ToyUtility::int16;
using ToyUtility::int32;
using ToyUtility::int64;
using ToyUtility::uint8;
using ToyUtility::uint16;
using ToyUtility::uint32;
using ToyUtility::uint64;

enum ToyRenderType
{
    ToyRenderOpenGL = TRL_OPENGL,
    ToyRenderOpenGLES = TRL_OPENGLES,
    ToyRenderDX11 = TRL_DX11,
};

enum class GpuVariableComponentSize
{
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
};


} // end of namespace TRL


#if defined(TRL_USING_OPENGL) || defined(TRL_USING_OPENGLES)
# include "TRL/details/GLCommonType.h"
#elif defined(TRL_USING_DX11)
# include "TRL/details/DX11CommonType.h"
#endif