#include "TRL/TRLSL/Tokener.h"


namespace TRL
{


void Tokener::Prepare(ToyUtility::DataStream & inputStream)
{
    m_Input = inputStream.GetAsString();
    m_Begin = m_Input.c_str();
    m_Length = m_Input.size();

    _ScanAll();
}

const Token& Tokener::NextToken()
{
    if(m_CurrToken >= m_Tokens.size())
        return ;

    return m_Tokens[m_CurrToken++];
}

void Tokener::_ScanAll()
{
    
}


} // end of namespace TRL