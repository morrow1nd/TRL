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
	
}

ToyUtility::SPtr<TRLShader> GLSLCodeGenerator::GenerateCode(TRLSL_IR &ir)
{
	return ToyUtility::SPtr<TRLShader>();
}


} // end of namespace TRL