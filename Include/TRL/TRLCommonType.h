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

enum class TRLNativeApiType
{
    OpenGL = TRL_OPENGL,
    OpenGLES = TRL_OPENGLES,
    DX11 = TRL_DX11,
};

enum class GpuVariableComponentSize
{
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
};

enum class NormalizeActionType
{
    NotNeedNormalize,
    NeedNormalize,
};


enum GpuPrimitiveType
{
    GPU_PRIMITIVE_TYPE_INIT = 0,

    GPU_POINTS,
    GPU_LINE_STRIP,
    GPU_LINE_LOOP,
    GPU_LINES,
    GPU_TRIANGLE_STRIP,
    GPU_TRIANGLE_FAN,
    GPU_TRIANGLES,
};

enum GpuDataType
{
    GPU_DATA_TYPE_INIT = 0,

    GPU_BOOL,

    GPU_INT8,
    GPU_UINT8,
    GPU_INT16,
    GPU_UINT16,
    GPU_INT32,
    GPU_UINT32,
    GPU_HALF_FLOAT,
    GPU_FLOAT,

    GPU_FLOAT_VEC2,
    GPU_FLOAT_VEC3,
    GPU_FLOAT_VEC4,
    GPU_INT32_VEC2,
    GPU_INT32_VEC3,
    GPU_INT32_VEC4,
    GPU_UINT32_VEC2,
    GPU_UINT32_VEC3,
    GPU_UINT32_VEC4,
    GPU_BOOL_VEC2,
    GPU_BOOL_VEC3,
    GPU_BOOL_VEC4,
    GPU_FLOAT_MAT2,
    GPU_FLOAT_MAT3,
    GPU_FLOAT_MAT4,
    GPU_FLOAT_MAT2x3,
    GPU_FLOAT_MAT2x4,
    GPU_FLOAT_MAT3x2,
    GPU_FLOAT_MAT3x4,
    GPU_FLOAT_MAT4x2,
    GPU_FLOAT_MAT4x3,
    GPU_SAMPLER_2D,
    GPU_SAMPLER_3D,
    GPU_SAMPLER_CUBE,
};

enum GpuBufferDataType
{
    GPU_BUFFER_DATA_TYPE_INIT = 0,

    GPU_STREAM_DRAW,
    GPU_STREAM_READ,
    GPU_STREAM_COPY,
    GPU_STATIC_DRAW,
    GPU_STATIC_READ,
    GPU_STATIC_COPY,
    GPU_DYNAMIC_DRAW,
    GPU_DYNAMIC_READ,
    GPU_DYNAMIC_COPY,
};

enum GpuBufferType
{
    GPU_BUFFER_TYPE_INIT = 0,

    GPU_ARRAY_BUFFER,
    GPU_ELEMENT_ARRAY_BUFFER,
    // and more...
};

enum GpuShaderType
{
    GPU_SHADER_TYPE_INIT = 0,

    GPU_VERTEX_SHADER,
    GPU_FRAGMENT_SHADER,
    GPU_COMPUTE_SHADER,
};

enum GpuTextureType
{
    GPU_TEXTURE_TYPE_INIT = 0,

    GPU_TEXTURE_2D,
    GPU_TEXTURE_3D,
    GPU_TEXTURE_2D_ARRAY,
    GPU_TEXTURE_CUBE_MAP,
    //GPU_TEXTURE_2D_MULTISAMPLE,
};

enum GpuTextureBaseFormat
{
    GPU_TEXTURE_BASE_FORMAT_INIT = 0,

    GPU_RED,
    GPU_RG,
    GPU_RGB,
    GPU_RGBA,
    GPU_LUMINANCE,
    GPU_LUMINANCE_ALPHA,
    GPU_ALPHA,
    GPU_DEPTH_COMPONENT,
    GPU_DEPTH_STENCIL,
    GPU_RED_INTEGER,
    GPU_RG_INTEGER,
    GPU_RGB_INTEGER,
    GPU_RGBA_INTEGER,
};

enum class PixelFormat
{
    PIXEL_FORMAT_INIT = 0,

    RED = GpuTextureBaseFormat::GPU_RED,
    RED_INTEGER = GpuTextureBaseFormat::GPU_RED_INTEGER,
    RG = GpuTextureBaseFormat::GPU_RG,
    RG_INTEGER = GpuTextureBaseFormat::GPU_RG_INTEGER,
    RGB = GpuTextureBaseFormat::GPU_RGB,
    RGB_INTEGER = GpuTextureBaseFormat::GPU_RGB_INTEGER,
    RGBA = GpuTextureBaseFormat::GPU_RGBA,
    RGBA_INTEGER = GpuTextureBaseFormat::GPU_RGBA_INTEGER,
    DEPTH_COMPONENT = GpuTextureBaseFormat::GPU_DEPTH_COMPONENT,
    DEPTH_STENCIL = GpuTextureBaseFormat::GPU_DEPTH_STENCIL,
    ALPHA = GpuTextureBaseFormat::GPU_ALPHA,
    LUMINANCE_ALPHA = GpuTextureBaseFormat::GPU_LUMINANCE_ALPHA,
    LUMINANCE = GpuTextureBaseFormat::GPU_LUMINANCE,
};

enum class PixelDataType
{
    PIXEL_DATA_TYPE_INIT = 0,

    UINT8 = GpuDataType::GPU_UINT8,
    INT8 = GpuDataType::GPU_INT8,
    UINT16 = GpuDataType::GPU_UINT16,
    INT16 = GpuDataType::GPU_INT16,
    UINT32 = GpuDataType::GPU_UINT32,
    INT32 = GpuDataType::GPU_INT32,
    HALF_FLOAT = GpuDataType::GPU_HALF_FLOAT,
    FLOAT = GpuDataType::GPU_FLOAT,

    //UNSIGNED_SHORT_5_6_5 = GpuDataType::GPU_UNSIGNED_SHORT_5_6_5,
    //GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_INT_2_10_10_10_REV, GL_UNSIGNED_INT_10F_11F_11F_REV, GL_UNSIGNED_INT_5_9_9_9_REV, GL_UNSIGNED_INT_24_8, and GL_FLOAT_32_UNSIGNED_INT_24_8_REV.
};

enum class GpuTextureMagFilterMode
{
    GPU_TEXTURE_MAG_FILTER_MODE_INIT = 0,

    NEAREST,
    LINEAR,
};

enum class GpuTextureMinFilterMode
{
    GPU_TEXTURE_MIN_FILTER_MODE_INIT = 0,

    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR,
    // http://docs.gl/es3/glTexParameter
};

enum class GpuTextureWrapMode
{
    GPU_TEXTURE_WRAP_MODE_INIT = 0,

    REPEAT,
    CLAMP_TO_EDGE,
    MIRRORED_REPEAT,
};

enum GpuTextureUnit
{
    GPU_TEXTURE_UNIT0 = 0,
    GPU_TEXTURE_UNIT1,
    GPU_TEXTURE_UNIT2,
    GPU_TEXTURE_UNIT3,
    GPU_TEXTURE_UNIT4,
    GPU_TEXTURE_UNIT5,
    GPU_TEXTURE_UNIT6,
    GPU_TEXTURE_UNIT7,
    GPU_TEXTURE_UNIT8,
    GPU_TEXTURE_UNIT9,
    GPU_TEXTURE_UNIT10,
    GPU_TEXTURE_UNIT11,
    GPU_TEXTURE_UNIT12,
    GPU_TEXTURE_UNIT13,
    GPU_TEXTURE_UNIT14,
    GPU_TEXTURE_UNIT15,
};


} // end of namespace TRL