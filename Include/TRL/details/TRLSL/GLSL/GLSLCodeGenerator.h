#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/TRLSL/TRLSLCodeGenerator.h"


namespace TRL
{


class GLSLCodeGenerator : TRLSLCodeGenerator
{
public:
	void SetHumanReadFormat(bool humanReadFormat);

	void SetIndentStr(const char* str);

	virtual void GenerateCode(TRLSL_IR & ir, ToyUtility::DataStream & stream) override;
	
	virtual ToyUtility::SPtr<TRLShader> GenerateCode(TRLSL_IR & ir) override;
};


} // end of namespace TRL