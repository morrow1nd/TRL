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
        m_GenerateComments(true),
		m_HumanReadableFormat(true),
		m_IndentStr("\t"),
        m_EndOfLineStr("\n")
	{}


public:
    void SetGenerateComments(bool hasComments);

	void SetHumanReadableFormat(bool humanReadableFormat);

	void SetIndentStr(const ToyUtility::String& str);

    void SetEndOfLineStr(const ToyUtility::String& eol);

	virtual void GenerateCode(TRLSL_IR & ir, ToyUtility::DataStream & stream) override;


private:
    ToyUtility::String _Type2Text(TRLSL_IR::Type type, ToyUtility::String identifierName);

    ToyUtility::String _GpuDataType2Text(GpuDataType type);

    void _WriteLine(const ToyUtility::String& str, ToyUtility::DataStream& stream);

    void _WriteEmptyLine(ToyUtility::DataStream& stream);


private:
    bool m_GenerateComments;
	bool m_HumanReadableFormat;
	ToyUtility::String m_IndentStr;
    ToyUtility::String m_EndOfLineStr;
};


} // end of namespace TRL