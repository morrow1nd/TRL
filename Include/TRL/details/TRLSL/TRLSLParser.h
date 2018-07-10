#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/TRLSL/TRLSL_IRGenerator.h"


namespace TRL
{


class TRLSLTokener;
class TRLCodeGenerator;
class TRLSL_IR;


class TRLSLParser
{
public:
    TRLSLParser();
    ~TRLSLParser();

	void GenerateTRLSL_IR(TRLSLTokener& tokener, TRLSL_IR& ir);


private:
    void* m_InnerParser; // Lemon parser
	TRLSL_IRGenerator m_IRGenerator;
};


} // end of namespace TRL