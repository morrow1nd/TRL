#include "TRL/RenderAPI.h"

#include "ToyUtility/Random/UUID.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLRenderAPI.h"
#include "TRL/details/RenderAPIImpl/DX11/DX11RenderAPI.h"


namespace TRL
{


int RenderAPI::GetGpuDataTypeSize(GpuDataType dataType)
{
    switch (dataType)
    {
    case GPU_BOOL:
        return sizeof(bool);
        break;
    case GPU_INT8:
        return sizeof(int8);
        break;
    case GPU_UINT8:
        return sizeof(uint8);
        break;
    case GPU_INT16:
        return sizeof(int16);
        break;
    case GPU_UINT16:
        return sizeof(uint16);
        break;
    case GPU_INT32:
        return sizeof(int32);
        break;
    case GPU_UINT32:
        return sizeof(uint32);
        break;
    case GPU_HALF_FLOAT:
        return sizeof(uint16);
        break;
    case GPU_FLOAT:
        return sizeof(float);
        break;
    case GPU_FLOAT_VEC2:
        return sizeof(float[2]);
        break;
    case GPU_FLOAT_VEC3:
        return sizeof(float[3]);
        break;
    case GPU_FLOAT_VEC4:
        return sizeof(float[4]);
        break;
    case GPU_INT32_VEC2:
        return sizeof(int32[2]);
        break;
    case GPU_INT32_VEC3:
        return sizeof(int32[3]);
        break;
    case GPU_INT32_VEC4:
        return sizeof(int32[4]);
        break;
    case GPU_UINT32_VEC2:
        return sizeof(uint32[2]);
        break;
    case GPU_UINT32_VEC3:
        return sizeof(uint32[3]);
        break;
    case GPU_UINT32_VEC4:
        return sizeof(uint32[4]);
        break;
    case GPU_BOOL_VEC2:
        return sizeof(bool[2]); // TODO: check this
        break;
    case GPU_BOOL_VEC3:
        return sizeof(bool[3]); // TODO: check this
        break;
    case GPU_BOOL_VEC4:
        return sizeof(bool[4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT2:
        return sizeof(float[2][2]);
        break;
    case GPU_FLOAT_MAT3:
        return sizeof(float[3][3]);
        break;
    case GPU_FLOAT_MAT4:
        return sizeof(float[4][4]);
        break;
    case GPU_FLOAT_MAT2x3:
        return sizeof(float[2][3]); // TODO: check this
        break;
    case GPU_FLOAT_MAT2x4:
        return sizeof(float[2][4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT3x2:
        return sizeof(float[3][2]); // TODO: check this
        break;
    case GPU_FLOAT_MAT3x4:
        return sizeof(float[3][4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT4x2:
        return sizeof(float[4][2]); // TODO: check this
        break;
    case GPU_FLOAT_MAT4x3:
        return sizeof(float[4][3]); // TODO: check this
        break;
    case GPU_SAMPLER_2D:
    case GPU_SAMPLER_3D:
    case GPU_SAMPLER_CUBE:
        return sizeof(ToyUtility::UUID);
        break;
    default:
        assert(false && ("RenderAPI::GetGpuDataTypeSize comes to default: " + dataType));
        break;
    }

    return 0;
}

ToyUtility::SPtr<RenderAPI> RenderAPI::CreateDefaultRenderAPI()
{
    return ToyUtility::SPtr<RenderAPI>(new TRL::details::OpenGLRenderAPI()); // TODOH
}

ToyUtility::SPtr<RenderAPI> RenderAPI::CreateRenderAPI(TRLNativeApiType type)
{
    switch (type)
    {
    case TRLNativeApiType::DX11:
        return ToyUtility::SPtr<RenderAPI>(new TRL::details::DX11RenderAPI());
        break;
    case TRLNativeApiType::OpenGL:
        return ToyUtility::SPtr<RenderAPI>(new TRL::details::OpenGLRenderAPI());
        break;
    case TRLNativeApiType::OpenGLES:

        break;
    }

    return ToyUtility::SPtr<RenderAPI>();
}


} // end of namespace TRL