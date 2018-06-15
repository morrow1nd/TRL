#pragma once

#include <cassert>
#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DesignPattern/ISingleton.h"
#include "TRLConfig.h"
#include "TRL/TRLCommonType.h"


namespace TRL
{

namespace details
{


#define TRL_GL_NATIVE(variable) TRLCommonTypeToNative::Instance().ToNative(variable)


struct TRLCommonTypeToNative : ToyUtility::ISingleton<TRLCommonTypeToNative>
{
    GLuint ToNative(GpuVariableComponentSize value)
    {
        return GpuVariableComponentSizeToNativeValue(value);
    }

    GLuint GpuVariableComponentSizeToNativeValue(GpuVariableComponentSize componentSize)
    {
        return (GLuint)componentSize;
    }

    GLboolean ToNative(NormalizeActionType value)
    {
        return NormalizeActionTypeToNativeValue(value);
    }

    GLboolean NormalizeActionTypeToNativeValue(NormalizeActionType type)
    {
        return type == NormalizeActionType::NeedNormalize ? GL_TRUE : GL_FALSE;
    }

    GLuint ToNative(GpuPrimitiveType value)
    {
        return GpuPrimitiveTypeToNativeValue(value);
    }

    GLuint GpuPrimitiveTypeToNativeValue(GpuPrimitiveType type)
    {
#if TRL_MORE_RUNTIME_CHECK
        switch (type)
        {
        case GPU_POINTS:
            return GL_POINTS;
        case GPU_LINE_STRIP:
            return GL_LINE_STRIP;
        case GPU_LINE_LOOP:
            return GL_LINE_LOOP;
        case GPU_LINES:
            return GL_LINES;
        case GPU_TRIANGLE_STRIP:
            return GL_TRIANGLE_STRIP;
        case GPU_TRIANGLE_FAN:
            return GL_TRIANGLE_FAN;
        case GPU_TRIANGLES:
            return GL_TRIANGLES;
        default:
            assert(false);
        }
        return 0;
#else
        // TODOM: using a array to convert
#endif
    }

    GLuint ToNative(GpuDataType value)
    {
        return GpuDataTypeToNativeValue(value);
    }

    GLuint GpuDataTypeToNativeValue(GpuDataType type)
    {
#if TRL_MORE_RUNTIME_CHECK
        switch (type)
        {
        case GPU_BOOL:
            return GL_BOOL;
        case GPU_INT8:
            return GL_BYTE;
        case GPU_UNSIGNED_BYTE:
            return GL_UNSIGNED_BYTE;
        case GPU_SHORT:
            return GL_SHORT;
        case GPU_UNSIGNED_SHORT:
            return GL_UNSIGNED_SHORT;
        case GPU_INT:
            return GL_INT;
        case GPU_UNSIGNED_INT:
            return GL_UNSIGNED_INT;
        case GPU_HALF_FLOAT:
            return GL_HALF_FLOAT;
        case GPU_FLOAT:
            return GL_FLOAT;
        case GPU_FLOAT_VEC2:
            return GL_FLOAT_VEC2;
        case GPU_FLOAT_VEC3:
            return GL_FLOAT_VEC3;
        case GPU_FLOAT_VEC4:
            return GL_FLOAT_VEC4;
        case GPU_INT_VEC2:
            return GL_INT_VEC2;
        case GPU_INT_VEC3:
            return GL_INT_VEC3;
        case GPU_INT_VEC4:
            return GL_INT_VEC4;
        case GPU_UNSIGNED_INT_VEC2:
            return GL_UNSIGNED_INT_VEC2;
        case GPU_UNSIGNED_INT_VEC3:
            return GL_UNSIGNED_INT_VEC3;
        case GPU_UNSIGNED_INT_VEC4:
            return GL_UNSIGNED_INT_VEC4;
        case GPU_BOOL_VEC2:
            return GL_BOOL_VEC2;
        case GPU_BOOL_VEC3:
            return GL_BOOL_VEC3;
        case GPU_BOOL_VEC4:
            return GL_BOOL_VEC4;
        case GPU_FLOAT_MAT2:
            return GL_FLOAT_MAT2;
        case GPU_FLOAT_MAT3:
            return GL_FLOAT_MAT3;
        case GPU_FLOAT_MAT4:
            return GL_FLOAT_MAT4;
        case GPU_FLOAT_MAT2x3:
            return GL_FLOAT_MAT2x3;
        case GPU_FLOAT_MAT2x4:
            return GL_FLOAT_MAT2x4;
        case GPU_FLOAT_MAT3x2:
            return GL_FLOAT_MAT3x2;
        case GPU_FLOAT_MAT3x4:
            return GL_FLOAT_MAT3x4;
        case GPU_FLOAT_MAT4x2:
            return GL_FLOAT_MAT4x2;
        case GPU_FLOAT_MAT4x3:
            return GL_FLOAT_MAT4x3;
        case GPU_SAMPLER_2D:
            return GL_SAMPLER_2D;
        case GPU_SAMPLER_3D:
            return GL_SAMPLER_3D;
        case GPU_SAMPLER_CUBE:
            return GL_SAMPLER_CUBE;
        default:
            assert(false);
        }
        return 0;
#else
        // TODOM: using a array to convert
#endif
    }

    GLuint ToNative(GpuBufferDataType value)
    {
        return GpuBufferDataTypeToNativeValue(value);
    }

    GLuint GpuBufferDataTypeToNativeValue(GpuBufferDataType type)
    {
#if TRL_MORE_RUNTIME_CHECK
        switch (type)
        {
        case GPU_STREAM_DRAW:
            return GL_STREAM_DRAW;
        case GPU_STREAM_READ:
            return GL_STREAM_READ;
        case GPU_STREAM_COPY:
            return GL_STREAM_COPY;
        case GPU_STATIC_DRAW:
            return GL_STATIC_DRAW;
        case GPU_STATIC_READ:
            return GL_STATIC_READ;
        case GPU_STATIC_COPY:
            return GL_STATIC_COPY;
        case GPU_DYNAMIC_DRAW:
            return GL_DYNAMIC_DRAW;
        case GPU_DYNAMIC_READ:
            return GL_DYNAMIC_READ;
        case GPU_DYNAMIC_COPY:
            return GL_DYNAMIC_COPY;
        default:
            assert(false);
        }
        return 0;
#else
        // TODOM: using a array to convert
#endif
    }

    GLuint ToNative(GpuBufferType value)
    {
        return GpuBufferTypeToNativeValue(value);
    }

    GLuint GpuBufferTypeToNativeValue(GpuBufferType type)
    {
        switch (type)
        {
        case GPU_ARRAY_BUFFER:
            return GL_ARRAY_BUFFER;
        case GPU_ELEMENT_ARRAY_BUFFER:
            return GL_ELEMENT_ARRAY_BUFFER;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(GpuShaderType value)
    {
        return GpuShaderTypeToNativeValue(value);
    }

    GLuint GpuShaderTypeToNativeValue(GpuShaderType type)
    {
        switch (type)
        {
        case GPU_VERTEX_SHADER:
            return GL_VERTEX_SHADER;
        case GPU_FRAGMENT_SHADER:
            return GL_FRAGMENT_SHADER;
        case GPU_COMPUTE_SHADER:
            return GL_COMPUTE_SHADER;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(GpuTextureType value)
    {
        return GpuTextureTypeToNativeValue(value);
    }

    GLuint GpuTextureTypeToNativeValue(GpuTextureType type)
    {
        switch (type)
        {
        case GPU_TEXTURE_2D:
            return GL_TEXTURE_2D;
        case GPU_TEXTURE_3D:
            return GL_TEXTURE_3D;
        case GPU_TEXTURE_2D_ARRAY:
            return GL_TEXTURE_2D_ARRAY;
        case GPU_TEXTURE_CUBE_MAP:
            return GL_TEXTURE_CUBE_MAP;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(GpuTextureBaseFormat value)
    {
        return GpuTextureBaseFormatToNativeValue(value);
    }

    GLuint GpuTextureBaseFormatToNativeValue(GpuTextureBaseFormat format)
    {
        switch (format)
        {
        case GPU_RED:
            return GL_RED;
        case GPU_RG:
            return GL_RG;
        case GPU_RGB:
            return GL_RGB;
        case GPU_RGBA:
            return GL_RGBA;
        case GPU_LUMINANCE:
            return GL_LUMINANCE;
        case GPU_LUMINANCE_ALPHA:
            return GL_LUMINANCE_ALPHA;
        case GPU_ALPHA:
            return GL_ALPHA;
        case GPU_DEPTH_COMPONENT:
            return GL_DEPTH_COMPONENT;
        case GPU_DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        case GPU_RED_INTEGER:
            return GL_RED_INTEGER;
        case GPU_RG_INTEGER:
            return GL_RG_INTEGER;
        case GPU_RGB_INTEGER:
            return GL_RGB_INTEGER;
        case GPU_RGBA_INTEGER:
            return GL_RGBA_INTEGER;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(PixelFormat value)
    {
        return PixelFormatToNativeValue(value);
    }

    GLuint PixelFormatToNativeValue(PixelFormat format)
    {
        return GpuTextureBaseFormatToNativeValue((GpuTextureBaseFormat)format);
    }

    GLuint ToNative(PixelDataType value)
    {
        return PixelDataTypeToNativeValue(value);
    }

    GLuint PixelDataTypeToNativeValue(PixelDataType type)
    {
        return GpuDataTypeToNativeValue((GpuDataType)type);
    }

    GLuint ToNative(GpuTextureMagFilterMode value)
    {
        return GpuTextureMagFilterModeToNativeValue(value);
    }

    GLuint GpuTextureMagFilterModeToNativeValue(GpuTextureMagFilterMode mode)
    {
        switch (mode)
        {
        case GpuTextureMagFilterMode::NEAREST:
            return GL_NEAREST;
        case GpuTextureMagFilterMode::LINEAR:
            return GL_LINEAR;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(GpuTextureMinFilterMode value)
    {
        return GpuTextureMinFilterModeToNativeValue(value);
    }

    GLuint GpuTextureMinFilterModeToNativeValue(GpuTextureMinFilterMode mode)
    {
        switch (mode)
        {
        case GpuTextureMinFilterMode::NEAREST:
            return GL_NEAREST;
        case GpuTextureMinFilterMode::LINEAR:
            return GL_LINEAR;
        case GpuTextureMinFilterMode::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case GpuTextureMinFilterMode::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case GpuTextureMinFilterMode::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case GpuTextureMinFilterMode::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(GpuTextureWrapMode value)
    {
        return GpuTextureWrapModeToNativeValue(value);
    }

    GLuint GpuTextureWrapModeToNativeValue(GpuTextureWrapMode mode)
    {
        switch (mode)
        {
        case GpuTextureWrapMode::REPEAT:
            return GL_REPEAT;
        case GpuTextureWrapMode::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case GpuTextureWrapMode::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        default:
            assert(false);
        }
        return 0;
    }

    GLuint ToNative(GpuTextureUnit value)
    {
        return GpuTextureUnitToNativeValue(value);
    }

    GLuint GpuTextureUnitToNativeValue(GpuTextureUnit unit)
    {
        return (GLuint)unit;
    }
};


} // end of namespace details

} // end of namespace TRL