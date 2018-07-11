#include "TRL/details/TRLSL/GLSL/GLSLCodeGenerator.h"

#include "TRL/details/TRLSL/TRLSL_IR.h"


namespace TRL
{


void GLSLCodeGenerator::SetHumanReadableFormat(bool humanReadableFormat)
{
	m_HumanReadableFormat = humanReadableFormat;
}

void GLSLCodeGenerator::SetIndentStr(const ToyUtility::String & str)
{
	m_IndentStr = str;
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
            
        }
    }
}

ToyUtility::SPtr<TRLShader> GLSLCodeGenerator::GenerateCode(TRLSL_IR &ir)
{
	return ToyUtility::SPtr<TRLShader>();
}


} // end of namespace TRL