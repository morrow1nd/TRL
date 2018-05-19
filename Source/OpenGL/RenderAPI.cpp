#include "TRL/RenderAPI.h"
#include "TRL/GpuProgram.h"
#include "TRL/AttributeData.h"


namespace TRL
{


int RenderAPI::GetGpuDataTypeSize(GpuDataType dataType)
{
    switch (dataType)
    {
    case GPU_BYTE:
        return sizeof(GLbyte);
        break;
    case GPU_UNSIGNED_BYTE:
        return sizeof(GLubyte);
        break;
    case GPU_SHORT:
        return sizeof(GLshort);
        break;
    case GPU_UNSIGNED_SHORT:
        return sizeof(GLushort);
        break;
    case GPU_INT:
        return sizeof(GLint);
        break;
    case GPU_UNSIGNED_INT:
        return sizeof(GLuint);
        break;
    case GPU_HALF_FLOAT:
        return sizeof(GLhalf);
        break;
    case GPU_FLOAT:
        return sizeof(GLfloat);
        break;
    case GPU_FIXED:
        return sizeof(GLfixed);
        break;
    case GPU_FLOAT_VEC2:
        return sizeof(GLfloat[2]);
        break;
    case GPU_FLOAT_VEC3:
        return sizeof(GLfloat[3]);
        break;
    case GPU_FLOAT_VEC4:
        return sizeof(GLfloat[4]);
        break;
    case GPU_INT_VEC2:
        return sizeof(GLint[2]);
        break;
    case GPU_INT_VEC3:
        return sizeof(GLint[3]);
        break;
    case GPU_INT_VEC4:
        return sizeof(GLint[4]);
        break;
    case GPU_UNSIGNED_INT_VEC2:
        return sizeof(GLuint[2]);
        break;
    case GPU_UNSIGNED_INT_VEC3:
        return sizeof(GLuint[3]);
        break;
    case GPU_UNSIGNED_INT_VEC4:
        return sizeof(GLuint[4]);
        break;
    case GPU_BOOL_VEC2:
        return sizeof(GLboolean[2]); // TODO: check this
        break;
    case GPU_BOOL_VEC3:
        return sizeof(GLboolean[3]); // TODO: check this
        break;
    case GPU_BOOL_VEC4:
        return sizeof(GLboolean[4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT2:
        return sizeof(GLfloat[2][2]);
        break;
    case GPU_FLOAT_MAT3:
        return sizeof(GLfloat[3][3]);
        break;
    case GPU_FLOAT_MAT4:
        return sizeof(GLfloat[4][4]);
        break;
    case GPU_FLOAT_MAT2x3:
        return sizeof(GLfloat[2][3]); // TODO: check this
        break;
    case GPU_FLOAT_MAT2x4:
        return sizeof(GLfloat[2][4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT3x2:
        return sizeof(GLfloat[3][2]); // TODO: check this
        break;
    case GPU_FLOAT_MAT3x4:
        return sizeof(GLfloat[3][4]); // TODO: check this
        break;
    case GPU_FLOAT_MAT4x2:
        return sizeof(GLfloat[4][2]); // TODO: check this
        break;
    case GPU_FLOAT_MAT4x3:
        return sizeof(GLfloat[4][3]); // TODO: check this
        break;
    //case GPU_SAMPLER_2D:
    //    return sizeof(GLbyte);
    //    break;
    //case GPU_SAMPLER_3D:
    //    return sizeof(GLbyte);
    //    break;
    //case GPU_SAMPLER_CUBE:
    //    return sizeof(GLbyte);
    //    break;
    // 
    // ......
    }

    assert(false && ("RenderAPI::GetGpuDataTypeSize comes to default: " + dataType));
    return 0;
}

TRLNativeApi RenderAPI::GetUsedNativeApi() const
{
#if defined(TRL_OPENGL)
    return TRLNativeApi::OpenGL;
#elif defined(TRL_OPENGLES)
    return TRLNativeApi::OpenGLES;
#else
# error TRL: Unknow Native Api.
#endif
}

void RenderAPI::ActiveGpuProgram(const GpuProgram& program)
{
    m_ActiveGpuProgram = program.m_ProgramInner;
    glUseProgram(m_ActiveGpuProgram);
}

bool RenderAPI::IsActiveGpuProgram(const GpuProgram & program)
{
    return program.m_ProgramInner == m_ActiveGpuProgram;
}

void RenderAPI::DrawIndices(GpuPrimitiveType mode, const AttributeData& attributeData, int offset)
{
    glDrawElements(mode, attributeData.GetIndicesNumber(), attributeData.GetIndicesDataType(),
        (const void*)offset);
}

void RenderAPI::ConvertProjectionMatrix(const ToyUtility::Matrix4 & matrix, ToyUtility::Matrix4 & dest)
{
    dest = matrix;
}


} // end of namespace TRL