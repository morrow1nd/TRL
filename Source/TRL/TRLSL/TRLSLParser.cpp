#include "TRL/TRLSL/TRLSLParser.h"

#include "./trlsl_parser.cpp"
#include <cstdlib>

#include "TRL/TRLSL/TRLSLTokener.h"
#include "TRL/TRLSL/TRLSLGenerator.h"


namespace TRL
{


bool TRLSLParser::Parse(TRLSLTokener & tokener, TRLSLGenerator & generator)
{
    void* parser = TrlSLParser_Alloc(malloc, &generator);

    if (generator.CanUseConstToken())
    {
        const Token* t = &tokener.NextToken();
        while (t != nullptr && t->Type != Token::None.Type)
        {
            TrlSLParser_(parser, t->Type, (Token*)t);
            t = &tokener.NextToken();
        }
    }
    else
    {
        tokener.CopyAllTokens(generator.GetInnerTokenPool());

        for each(auto& token in generator.GetInnerTokenPool())
        {
            TrlSLParser_(parser, token.Type, (Token*)(&token));
        }
    }

    TrlSLParser_(parser, 0, nullptr);
    TrlSLParser_Free(parser, free);
    return true; // TODOH
}


} // end of namespace TRL