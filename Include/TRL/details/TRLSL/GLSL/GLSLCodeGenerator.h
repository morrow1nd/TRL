#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "TRL/details/TRLSL/TRLSLCodeGenerator.h"


namespace TRL
{


class GLSLCodeGenerator : TRLSLCodeGenerator
{
public:
	GLSLCodeGenerator()
		:
		m_HumanReadableFormat(true),
		m_IndentStr("\t")
	{}


public:
	void SetHumanReadableFormat(bool humanReadableFormat);

	void SetIndentStr(const ToyUtility::String& str);

	virtual void GenerateCode(TRLSL_IR & ir, ToyUtility::DataStream & stream) override;
	
	virtual ToyUtility::SPtr<TRLShader> GenerateCode(TRLSL_IR & ir) override;


private:
	bool m_HumanReadableFormat;
	ToyUtility::String m_IndentStr;
};


} // end of namespace TRL