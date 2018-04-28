#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRLConfig.h"

#if defined(TRL_USING_OPENGL) || defined(TRL_USING_OPENGLES)
# include "glad/glad.h"
#endif


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


#if defined(TRL_USING_OPENGL) || defined(TRL_USING_OPENGLES)

using GpuBufferObjectInner = GLuint;
using GpuVAOInner = GLuint;
using GpuShaderInner = GLuint;
using GpuProgramInner = GLuint;

using GpuBool = GLboolean;
using GpuVoid = GLvoid;
using GpuByte = GLbyte;
using GpuShort = GLshort;
using GpuInt = GLint;
using GpuClampx = GLclampx;
using GpuUByte = GLubyte;
using GpuUShort = GLushort;
using GpuUInt = GLuint;
using GpuSizei = GLsizei;
using GpuFloat = GLfloat;
using GpuClampf = GLclampf;
using GpuDouble = GLdouble;
using GpuClampd = GLclampd;
//using Gpu = GLeglImageOES;
using Gpu = GLchar;
using Gpu = GLcharARB;
using GpuFloat = GLfloat;


enum GpuPrimitiveType
{
    GPU_PRIMITIVE_TYPE_INIT = 0,

    GPU_POINTS = GL_POINTS,
    GPU_LINE_STRIP = GL_LINE_STRIP,
    GPU_LINE_LOOP = GL_LINE_LOOP,
    GPU_LINES = GL_LINES,
    GPU_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    GPU_TRIANGLE_FAN = GL_TRIANGLE_FAN,
    GPU_TRIANGLES = GL_TRIANGLES,
};

enum GpuDataType
{
    GPU_DATA_TYPE_INIT = 0,

    GPU_BYTE = GL_BYTE,
    GPU_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    GPU_SHORT = GL_SHORT,
    GPU_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    GPU_INT = GL_INT,
    GPU_UNSIGNED_INT = GL_UNSIGNED_INT,
    GPU_HALF_FLOAT = GL_HALF_FLOAT,
    GPU_FLOAT = GL_FLOAT,
    GPU_FIXED = GL_FIXED,
    GPU_INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
    GPU_UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
};

enum GpuBufferDataType
{
    GPU_BUFFER_DATA_TYPE_INIT = 0,

    GPU_STREAM_DRAW = GL_STREAM_DRAW,
    GPU_STREAM_READ = GL_STREAM_READ,
    GPU_STREAM_COPY = GL_STREAM_COPY,
    GPU_STATIC_DRAW = GL_STATIC_DRAW,
    GPU_STATIC_READ = GL_STATIC_READ,
    GPU_STATIC_COPY = GL_STATIC_COPY,
    GPU_DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    GPU_DYNAMIC_READ = GL_DYNAMIC_READ,
    GPU_DYNAMIC_COPY = GL_DYNAMIC_COPY,
};

enum GpuBufferType
{
    GPU_BUFFER_TYPE_INIT = 0,

    GPU_ARRAY_BUFFER = GL_ARRAY_BUFFER,
    GPU_ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
    // and more...
};

enum GpuShaderType
{
    GPU_SHADER_TYPE_INIT = 0,

    GPU_VERTEX_SHADER = GL_VERTEX_SHADER,
    GPU_FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    GPU_COMPUTE_SHADER = GL_COMPUTE_SHADER,
};


#endif


} // end of namespace TRL