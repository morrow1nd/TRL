#include "TRL/details/TRLSL/HLSLGenerator.h"

#include <sstream>
#include "ToyUtility/DataStream/DataStream.h"


namespace TRL
{


Token* HLSLGenerator::NextToken(bool restart)
{
    if(restart)
        m_CurrToken = 0;

    if (m_CurrToken < m_Tokens.size())
    {
        return (Token*)&m_TokenPool[m_Tokens[m_CurrToken++]];
    }

    return nullptr;
}

void HLSLGenerator::SetAllTokens(const ToyUtility::List<Token>& tokens)
{
    m_TokenHelpers.clear();
    m_TokenPool.clear();

    m_TokenHelpers.push_back(TokenHelper());
    m_TokenPool.push_back(Token::__None);

    for each(auto token in tokens)
    {
        m_TokenPool.push_back(token);

        m_Tokens.push_back(m_TokenPool.size() - 1);
        m_TokenHelpers.push_back(TokenHelper());

        m_TokenPool.back().SetUserData((void*)(m_TokenHelpers.size() - 1));
        m_TokenHelpers.back().TokenIndex = m_TokenPool.size() - 1;
    }
}

void HLSLGenerator::GenerateCode(ToyUtility::DataStream& stream) const
{
    stream.WriteString("#version 330 core\n");

    // TODOH

    //for (size_t tokenIndex = m_RootToken; tokenIndex != 0 && tokenIndex < m_TokenPool.size(); )
    //{
    //    const Token& t = m_TokenPool[tokenIndex];
    //    size_t thIndex = (size_t)t.GetUserData();
    //    // TODOL: check thIndex range
    //    const TokenHelper& th = m_TokenHelpers[thIndex];

    //    if (t.IsTerminalSymbol())
    //    {
    //        stream.Write(t.Str, t.StrLen);
    //        stream.Write(" ", 1);
    //    }

    //    tokenIndex = th.Next;
    //}
}

ToyUtility::String HLSLGenerator::GenerateCode() const
{
    std::stringstream stream;

    // TODOM: I don't write the same code twice
    stream << "#version 330 core\n";

    // TODOH

    //for (size_t tokenIndex = m_RootToken; tokenIndex != 0 && tokenIndex < m_TokenPool.size(); )
    //{
    //    const Token& t = m_TokenPool[tokenIndex];
    //    size_t thIndex = (size_t)t.GetUserData();
    //    // TODOL: check thIndex range
    //    const TokenHelper& th = m_TokenHelpers[thIndex];

    //    if (t.IsTerminalSymbol())
    //    {
    //        stream.write(t.Str, t.StrLen);
    //        stream.write(" ", 1);
    //    }

    //    tokenIndex = th.Next;
    //}

    return stream.str();
}

Token& HLSLGenerator::_NewToken(Token t)
{
    m_TokenHelpers.push_back(TokenHelper());
    m_TokenPool.push_back(t);
    m_TokenPool.back().SetUserData((void*)(m_TokenHelpers.size() - 1));
    m_TokenHelpers.back().TokenIndex = m_TokenPool.size() - 1;
    return m_TokenPool.back();
}

// TODOL: Remove unused arguments
TRLSLGenerator::RetType HLSLGenerator::variable_identifier__To__IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::primary_expression__To__variable_identifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::primary_expression__To__INTCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::primary_expression__To__UINTCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::primary_expression__To__FLOATCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::primary_expression__To__BOOLCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::primary_expression__To__LS___expression___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::postfix_expression__To__primary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::postfix_expression__To__postfix_expression___LM___integer_expression___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::postfix_expression__To__function_call(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::postfix_expression__To__postfix_expression___DOT___FIELD_SELECTION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::postfix_expression__To__postfix_expression___INC_OP(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::postfix_expression__To__postfix_expression___DEC_OP(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::integer_expression__To__expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call__To__function_call_or_method(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_or_method__To__function_call_generic(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_generic__To__function_call_header_with_parameters___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_generic__To__function_call_header_no_parameters___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_header_no_parameters__To__function_call_header___VOID(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_header_no_parameters__To__function_call_header(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_header_with_parameters__To__function_call_header___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_header_with_parameters__To__function_call_header_with_parameters___COMMA___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_call_header__To__function_identifier___LS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_identifier__To__type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_identifier__To__postfix_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_expression__To__postfix_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_expression__To__INC_OP___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_expression__To__DEC_OP___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_expression__To__unary_operator___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_operator__To__PLUS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_operator__To__DASH(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_operator__To__BANG(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::unary_operator__To__TILDE(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::multiplicative_expression__To__unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::multiplicative_expression__To__multiplicative_expression___STAR___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::multiplicative_expression__To__multiplicative_expression___SLASH___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::multiplicative_expression__To__multiplicative_expression___PERCENT___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::additive_expression__To__multiplicative_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::additive_expression__To__additive_expression___PLUS___multiplicative_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::additive_expression__To__additive_expression___DASH___multiplicative_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::shift_expression__To__additive_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::shift_expression__To__shift_expression___LEFT_OP___additive_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::shift_expression__To__shift_expression___RIGHT_OP___additive_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::relational_expression__To__shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::relational_expression__To__relational_expression___LEFT_ANGLE___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::relational_expression__To__relational_expression___RIGHT_ANGLE___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::relational_expression__To__relational_expression___LE_OP___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::relational_expression__To__relational_expression___GE_OP___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::equality_expression__To__relational_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::equality_expression__To__equality_expression___EQ_OP___relational_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::equality_expression__To__equality_expression___NE_OP___relational_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::and_expression__To__equality_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::and_expression__To__and_expression___AMPERSAND___equality_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::exclusive_or_expression__To__and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::exclusive_or_expression__To__exclusive_or_expression___CARET___and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::inclusive_or_expression__To__exclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::inclusive_or_expression__To__inclusive_or_expression___VERTICAL_BAR___exclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::logical_and_expression__To__inclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::logical_and_expression__To__logical_and_expression___AND_OP___inclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::logical_or_expression__To__logical_and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::logical_or_expression__To__logical_or_expression___OR_OP___logical_and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::conditional_expression__To__logical_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::conditional_expression__To__logical_or_expression___QUESTION___expression___COLON___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_expression__To__conditional_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_expression__To__unary_expression___assignment_operator___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__EQUAL(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__MUL_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__DIV_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__MOD_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__ADD_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__SUB_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__LEFT_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__RIGHT_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__AND_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__XOR_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::assignment_operator__To__OR_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::expression__To__assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::expression__To__expression___COMMA___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::constant_expression__To__conditional_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::declaration__To__init_declarator_list___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_prototype__To__function_declarator___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_declarator__To__function_header(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_declarator__To__function_header_with_parameters(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_header_with_parameters__To__function_header___parameter_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_header_with_parameters__To__function_header_with_parameters___COMMA___parameter_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_header__To__fully_specified_type___IDENTIFIER___LS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_declarator__To__type_specifier___IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_declarator__To__type_specifier___IDENTIFIER___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_declaration__To__type_qualifier___parameter_declarator(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_declaration__To__parameter_declarator(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_declaration__To__type_qualifier___parameter_type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_declaration__To__parameter_type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::parameter_type_specifier__To__type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::init_declarator_list__To__single_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_declaration__To__fully_specified_type(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::fully_specified_type__To__type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::fully_specified_type__To__type_qualifier___type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_qualifier__To__single_type_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_qualifier__To__type_qualifier___single_type_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_type_qualifier__To__storage_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::single_type_qualifier__To__precision_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::storage_qualifier__To__CONST(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::storage_qualifier__To__IN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::storage_qualifier__To__OUT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::storage_qualifier__To__INOUT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::storage_qualifier__To__UNIFORM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier__To__type_specifier_nonarray(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier__To__type_specifier_nonarray___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::array_specifier__To__LM___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::array_specifier__To__LM___constant_expression___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::array_specifier__To__array_specifier___LM___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::array_specifier__To__array_specifier___LM___constant_expression___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__VOID(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__FLOAT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__INT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__UINT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__BOOL(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__VEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__VEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__VEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__BVEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__BVEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__BVEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__IVEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__IVEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__IVEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__UVEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__UVEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__UVEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT2X2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT2X3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT2X4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT3X2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT3X3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT3X4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT4X2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT4X3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__MAT4X4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__SAMPLER2D(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__SAMPLER3D(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::type_specifier_nonarray__To__SAMPLERCUBE(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::precision_qualifier__To__HIGH_PRECISION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::precision_qualifier__To__MEDIUM_PRECISION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::precision_qualifier__To__LOW_PRECISION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::initializer__To__assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::declaration_statement__To__declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::statement__To__compound_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::statement__To__simple_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::simple_statement__To__declaration_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::simple_statement__To__expression_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::simple_statement__To__selection_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::simple_statement__To__iteration_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::simple_statement__To__jump_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::compound_statement__To__LB___RB(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::compound_statement__To__LB___statement_list___RB(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::statement_list__To__statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::statement_list__To__statement_list___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::expression_statement__To__SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::expression_statement__To__expression___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::selection_statement__To__IF___LS___expression___RS___selection_rest_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::selection_rest_statement__To__statement___ELSE___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::selection_rest_statement__To__statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::condition__To__expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::condition__To__fully_specified_type___IDENTIFIER___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::iteration_statement__To__WHILE___LS___condition___RS___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::iteration_statement__To__FOR___LS___for_init_statement___for_rest_statement___RS___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::for_init_statement__To__expression_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::for_init_statement__To__declaration_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::condition_opt__To__condition(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::condition_opt__To__Empty(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = &_NewToken(Token::__None);
}

TRLSLGenerator::RetType HLSLGenerator::for_rest_statement__To__condition_opt___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::for_rest_statement__To__condition_opt___SEMICOLON___expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::jump_statement__To__CONTINUE___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::jump_statement__To__BREAK___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::jump_statement__To__RETURN___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::jump_statement__To__RETURN___expression___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::jump_statement__To__DISCARD___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::translation_unit__To__external_declaration_list(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
    m_RootToken = _GetTokenId(*_);
}

TRLSLGenerator::RetType HLSLGenerator::external_declaration_list__To__external_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::external_declaration_list__To__external_declaration_list___external_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::external_declaration__To__function_definition(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::external_declaration__To__declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}

TRLSLGenerator::RetType HLSLGenerator::function_definition__To__function_prototype___compound_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    
}


} // end of namespace TRL