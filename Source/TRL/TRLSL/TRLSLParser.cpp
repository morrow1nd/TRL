#include "TRL/details/TRLSL/TRLSLParser.h"

#include "./trlsl_parser.cpp"
#include <cstdlib>

#include "TRL/details/TRLSL/TRLSLTokener.h"
#include "TRL/details/TRLSL/TRLSLCodeGenerator.h"


namespace TRL
{


TRLSLParser::TRLSLParser()
    :
    m_InnerParser(nullptr)
{
    m_InnerParser = TrlSLParser_Alloc(malloc, &m_IRGenerator);
}

TRLSLParser::~TRLSLParser()
{
    TrlSLParser_Free(m_InnerParser, free);
}

void TRLSLParser::GenerateTRLSL_IR(TRLSLTokener & tokener, TRLSL_IR & ir)
{
    m_IRGenerator.SetAllTokens(tokener.GetAllTokens());

    for (Token* t = m_IRGenerator.NextToken(true);
        t != nullptr;
        t = m_IRGenerator.NextToken())
    {
        TrlSLParser_(m_InnerParser, t->Type, t);
    }
    TrlSLParser_(m_InnerParser, 0, nullptr); // End token

	m_IRGenerator.GenerateIR(ir);

    //return true; // TODOH
}


} // end of namespace TRL