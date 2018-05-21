#include "TRL/TRLSL/TRLSLParser.h"

#include "./trlsl_parser.cpp"
#include <cstdlib>

#include "TRL/TRLSL/TRLSLTokener.h"
#include "TRL/TRLSL/TRLSLGenerator.h"


namespace TRL
{


TRLSLParser::TRLSLParser(TRLSLGenerator& generator)
    :
    m_Generator(generator),
    m_InnerParser(nullptr)
{
    m_InnerParser = TrlSLParser_Alloc(malloc, &generator);
}

TRLSLParser::~TRLSLParser()
{
    TrlSLParser_Free(m_InnerParser, free);
}


bool TRLSLParser::Parse(TRLSLTokener & tokener)
{
    m_Generator.SetAllTokens(tokener.GetAllTokens());

    for (Token* t = m_Generator.NextToken(true);
        t != nullptr;
        t = m_Generator.NextToken())
    {
        TrlSLParser_(m_InnerParser, t->Type, t);
    }
    TrlSLParser_(m_InnerParser, 0, nullptr); // End token

    return true; // TODOH
}


} // end of namespace TRL