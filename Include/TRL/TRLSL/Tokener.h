#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DataStream/DataStream.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "TRL/CommonType.h"
#include "TRL/TRLSL/Token.h"


namespace TRL
{


class Tokener
{
public:
    Tokener()
        :
        m_Begin(nullptr),
        m_Length(0),
        m_CurrToken(0)
    { }


public:
    void Prepare(ToyUtility::DataStream& inputStream);

    const Token& NextToken();


private:
    void _ScanAll();


private:
    ToyUtility::String m_Input;
    const char* m_Begin;
    int m_Length;
    ToyUtility::List<Token> m_Tokens;
    int m_CurrToken;
};


} // end of namespace TRL