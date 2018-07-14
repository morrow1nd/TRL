#include "TRL/details/TRLSL/GLSL/GLSLCodeGenerator.h"

#include "TRL/details/TRLSL/TRLSL_IR.h"


namespace TRL
{


void GLSLCodeGenerator::SetGenerateComments(bool hasComments)
{
    m_GenerateComments = hasComments;
}

void GLSLCodeGenerator::SetHumanReadableFormat(bool humanReadableFormat)
{
	m_HumanReadableFormat = humanReadableFormat;
}

void GLSLCodeGenerator::SetIndentStr(const ToyUtility::String & str)
{
	m_IndentStr = str;
}

void GLSLCodeGenerator::SetEndOfLineStr(const ToyUtility::String & eol)
{
    m_EndOfLineStr = eol;
}

void GLSLCodeGenerator::GenerateCode(TRLSL_IR &ir, ToyUtility::DataStream & stream)
{
	// vertex shader
    auto& pragma = ir.FindPragma(TRLSL_IR::PragmaCmdType::Vertex);
    if (pragma.IsValid())
    {
        auto& function = ir.FindFunction(pragma.FunctionName);
        if (function.IsValid())
        {
            _WriteLine("#version 330 core", stream);
            _WriteEmptyLine(stream);

            // Uniform variables
            {
                auto& uniforms = ir.GetUniformVariables();
                for each(auto& uniform in uniforms)
                {
                    if (uniform.Type.GetTag(TRLSL_IR::Type::TypeBitsets::Struct))
                    {
                        auto& stut = ir.FindStruct(uniform.Type.Str);
                        if (stut.IsValid())
                        {
                            
                        }
                        else
                        {
                            // TODOH
                        }
                    }
                    else
                    {
                        _WriteLine("uniform " + _Type2Text(uniform.Type, uniform.Name.ToString()), stream);
                    }
                }
            }

            // Vertex input
            {
                auto& params = function.Params;
                if (params.size() != 1)
                {
                    // TODOH

                    return;
                }

                auto& vsInput = ir.FindStruct(params.front().Name);
                if (!vsInput.IsValid())
                {
                    // TODOH
                    
                    return;
                }

                
            }
        }
    }
}

ToyUtility::String GLSLCodeGenerator::_Type2Text(TRLSL_IR::Type type, ToyUtility::String identifierName)
{
    ToyUtility::String ret;
    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Const))
        ret = "const";

    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::In) && type.GetTag(TRLSL_IR::Type::TypeBitsets::Out) == false)
        ret += " in";
    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Out) && type.GetTag(TRLSL_IR::Type::TypeBitsets::In) == false)
        ret += " out";
    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Out) && type.GetTag(TRLSL_IR::Type::TypeBitsets::In))
        ret += " inout";

    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Highp))
        ret += " highp";
    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Mediump))
        ret += " mediump";
    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Lowp))
        ret += " lowp";

    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Void))
        return "void"; // End
    
    if (type.GetTag(TRLSL_IR::Type::TypeBitsets::Struct))
    {
        // TODOH
    }
    else
    {
        ret += _GpuDataType2Text(type.DataType);
    }

    ret += identifierName;

    if (type.IsArray())
    {
        for (int i = 0; i < type.GetArraySize(); ++i)
        {
            if (type.Arrays[i] != 1)
            {
                ret += "[";
                ret += type.Arrays[i];
                ret += "]";
            }
            else
            {
                break;
            }
        }
    }

    return ret;
}

ToyUtility::String GLSLCodeGenerator::_GpuDataType2Text(GpuDataType type)
{
    switch (type)
    {
    case GpuDataType::GPU_BOOL:
        return "bool";
    case GpuDataType::GPU_INT8:
    case GpuDataType::GPU_INT16:
    case GpuDataType::GPU_INT32:
        return "int";
    case GpuDataType::GPU_UINT8:
    case GpuDataType::GPU_UINT16:
    case GpuDataType::GPU_UINT32:
        return "uint";
    case GpuDataType::GPU_FLOAT:
    case GpuDataType::GPU_HALF_FLOAT:
        return "float";
    case GpuDataType::GPU_FLOAT_VEC2:
        return "vec2";
    case GpuDataType::GPU_FLOAT_VEC3:
        return "vec3";
    case GpuDataType::GPU_FLOAT_VEC4:
        return "vec4";
    case GpuDataType::GPU_INT32_VEC2:
        return "ivec2";
    case GpuDataType::GPU_INT32_VEC3:
        return "ivec3";
    case GpuDataType::GPU_INT32_VEC4:
        return "ivec4";
    case GpuDataType::GPU_UINT32_VEC2:
        return "uvec2";
    case GpuDataType::GPU_UINT32_VEC3:
        return "uvec3";
    case GpuDataType::GPU_UINT32_VEC4:
        return "uvec4";
    case GpuDataType::GPU_BOOL_VEC2:
        return "bvec2";
    case GpuDataType::GPU_BOOL_VEC3:
        return "bvec3";
    case GpuDataType::GPU_BOOL_VEC4:
        return "bvec4";
    case GpuDataType::GPU_FLOAT_MAT2:
        return "mat2";
    case GpuDataType::GPU_FLOAT_MAT3:
        return "mat3";
    case GpuDataType::GPU_FLOAT_MAT4:
        return "mat4";
    case GpuDataType::GPU_FLOAT_MAT2x3:
        return "mat2x3";
    case GpuDataType::GPU_FLOAT_MAT2x4:
        return "mat2x4";
    case GpuDataType::GPU_FLOAT_MAT3x2:
        return "mat3x2";
    case GpuDataType::GPU_FLOAT_MAT3x4:
        return "mat3x4";
    case GpuDataType::GPU_FLOAT_MAT4x2:
        return "mat4x2";
    case GpuDataType::GPU_FLOAT_MAT4x3:
        return "mat4x3";
    case GpuDataType::GPU_SAMPLER_2D:
        return "sampler2D";
    case GpuDataType::GPU_SAMPLER_3D:
        return "sampler3D";
    case GpuDataType::GPU_SAMPLER_CUBE:
        return "samplerCube";
    default:
        break;
    }

    return "Error: Unknown GpuDataType";
}

void GLSLCodeGenerator::_WriteLine(const ToyUtility::String & str, ToyUtility::DataStream & stream)
{
    stream.WriteString(str);
    stream.WriteString(m_EndOfLineStr);
}

void GLSLCodeGenerator::_WriteEmptyLine(ToyUtility::DataStream & stream)
{
    stream.WriteString(m_EndOfLineStr);
}


} // end of namespace TRL