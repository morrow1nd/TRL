#include "TRL/details/TRLSL/TRLSL_IRGenerator.h"

#include <sstream>
#include "ToyUtility/DataStream/DataStream.h"


namespace TRL
{


Token* TRLSL_IRGenerator::NextToken(bool restart)
{
    if (restart)
        m_CurrToken = 0;

    if (m_CurrToken < (int)m_Tokens.size())
    {
        return (Token*)&m_TokenPool[m_Tokens[m_CurrToken++]];
    }

    return nullptr;
}

void TRLSL_IRGenerator::SetAllTokens(const ToyUtility::List<Token>& tokens)
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

void TRLSL_IRGenerator::GenerateIR(TRLSL_IR & ir)
{
    // TODOH
}

Token * TRLSL_IRGenerator::_GetLastOne(Token * t)
{
    auto th = _GetTokenHelper(t);
    if (th->Last == 0)
    {
        // TODOM: check th->Next == 0
        return t;
    }
    else
    {
        return &m_TokenPool[th->Last];
    }
}

int TRLSL_IRGenerator::_GetLastOneId(Token * t)
{
    auto th = _GetTokenHelper(t);
    if (th->Last == 0)
    {
        // TODO
        return th->TokenIndex;
    }
    else
    {
        return th->Last;
    }
}

void TRLSL_IRGenerator::_LinkTokens(Token * _1, Token * _2, Token * _3, Token * _4, Token * _5, Token * _6, Token * _7)
{
    auto th = _GetTokenHelper(_1);

    Token* end = nullptr;

    if (_2 != nullptr)
    {
        _LinkTokens(_1, _2); end = _2;
    }
    if (_3 != nullptr)
    {
        _LinkTokens(_2, _3); end = _3;
    }
    if (_4 != nullptr)
    {
        _LinkTokens(_3, _4); end = _4;
    }
    if (_5 != nullptr)
    {
        _LinkTokens(_4, _5); end = _5;
    }
    if (_6 != nullptr)
    {
        _LinkTokens(_5, _6); end = _6;
    }
    if (_7 != nullptr)
    {
        _LinkTokens(_6, _7); end = _7;
    }

    if (end != nullptr)
    {
        th->Last = _GetTokenId(_GetLastOne(end));
    }
}

void TRLSL_IRGenerator::_LinkTokens(Token* a, Token* b)
{
    if (a == nullptr)
        return;

    auto last = _GetLastOne(a);
    _GetTokenHelper(last)->Next = _GetTokenId(b);
    _GetTokenHelper(a)->Last = _GetLastOneId(b);
}

Token& TRLSL_IRGenerator::_NewToken(Token t)
{
    m_TokenHelpers.push_back(TokenHelper());
    m_TokenPool.push_back(t);
    m_TokenPool.back().SetUserData((void*)(m_TokenHelpers.size() - 1));
    m_TokenHelpers.back().TokenIndex = m_TokenPool.size() - 1;
    return m_TokenPool.back();
}

// TODOL: Remove unused arguments
TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::variable_identifier__To__IDENTIFIER(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::primary_expression__To__variable_identifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::primary_expression__To__INTCONSTANT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::primary_expression__To__UINTCONSTANT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::primary_expression__To__FLOATCONSTANT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::primary_expression__To__BOOLCONSTANT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::primary_expression__To__LS___expression___RS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::postfix_expression__To__primary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::postfix_expression__To__postfix_expression___LM___integer_expression___RM(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::postfix_expression__To__function_call(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::postfix_expression__To__postfix_expression___DOT___FIELD_SELECTION(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::postfix_expression__To__postfix_expression___INC_OP(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::postfix_expression__To__postfix_expression___DEC_OP(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::integer_expression__To__expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call__To__function_call_or_method(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_or_method__To__function_call_generic(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_generic__To__function_call_header_with_parameters___RS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_generic__To__function_call_header_no_parameters___RS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_header_no_parameters__To__function_call_header___VOID(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_header_no_parameters__To__function_call_header(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_header_with_parameters__To__function_call_header___assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_header_with_parameters__To__function_call_header_with_parameters___COMMA___assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_call_header__To__function_identifier___LS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_identifier__To__type_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_identifier__To__postfix_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_expression__To__postfix_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_expression__To__INC_OP___unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_expression__To__DEC_OP___unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_expression__To__unary_operator___unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_operator__To__PLUS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_operator__To__DASH(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_operator__To__BANG(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::unary_operator__To__TILDE(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::multiplicative_expression__To__unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::multiplicative_expression__To__multiplicative_expression___STAR___unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::multiplicative_expression__To__multiplicative_expression___SLASH___unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::multiplicative_expression__To__multiplicative_expression___PERCENT___unary_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::additive_expression__To__multiplicative_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::additive_expression__To__additive_expression___PLUS___multiplicative_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::additive_expression__To__additive_expression___DASH___multiplicative_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::shift_expression__To__additive_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::shift_expression__To__shift_expression___LEFT_OP___additive_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::shift_expression__To__shift_expression___RIGHT_OP___additive_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::relational_expression__To__shift_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::relational_expression__To__relational_expression___LEFT_ANGLE___shift_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::relational_expression__To__relational_expression___RIGHT_ANGLE___shift_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::relational_expression__To__relational_expression___LE_OP___shift_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::relational_expression__To__relational_expression___GE_OP___shift_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::equality_expression__To__relational_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::equality_expression__To__equality_expression___EQ_OP___relational_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::equality_expression__To__equality_expression___NE_OP___relational_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::and_expression__To__equality_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::and_expression__To__and_expression___AMPERSAND___equality_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::exclusive_or_expression__To__and_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::exclusive_or_expression__To__exclusive_or_expression___CARET___and_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::inclusive_or_expression__To__exclusive_or_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::inclusive_or_expression__To__inclusive_or_expression___VERTICAL_BAR___exclusive_or_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::logical_and_expression__To__inclusive_or_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::logical_and_expression__To__logical_and_expression___AND_OP___inclusive_or_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::logical_or_expression__To__logical_and_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::logical_or_expression__To__logical_or_expression___OR_OP___logical_and_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::conditional_expression__To__logical_or_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::conditional_expression__To__logical_or_expression___QUESTION___expression___COLON___assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_expression__To__conditional_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_expression__To__unary_expression___assignment_operator___assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__EQUAL(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__MUL_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__DIV_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__MOD_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__ADD_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__SUB_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__LEFT_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__RIGHT_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__AND_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__XOR_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::assignment_operator__To__OR_ASSIGN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::expression__To__assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::expression__To__expression___COMMA___assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::constant_expression__To__conditional_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::declaration__To__init_declarator_list___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_prototype__To__function_declarator___RS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_declarator__To__function_header(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_declarator__To__function_header_with_parameters(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_header_with_parameters__To__function_header___parameter_declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_header_with_parameters__To__function_header_with_parameters___COMMA___parameter_declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_header__To__fully_specified_type___IDENTIFIER___LS(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_declarator__To__type_specifier___IDENTIFIER(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_declarator__To__type_specifier___IDENTIFIER___array_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_declaration__To__type_qualifier___parameter_declarator(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_declaration__To__parameter_declarator(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_declaration__To__type_qualifier___parameter_type_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_declaration__To__parameter_type_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::parameter_type_specifier__To__type_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::init_declarator_list__To__single_declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier___EQUAL___initializer(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___EQUAL___initializer(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_declaration__To__fully_specified_type(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_declaration__To__fully_specified_type___IDENTIFIER(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier___EQUAL___initializer(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___EQUAL___initializer(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::fully_specified_type__To__type_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::fully_specified_type__To__type_qualifier___type_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_qualifier__To__single_type_qualifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_qualifier__To__type_qualifier___single_type_qualifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_type_qualifier__To__storage_qualifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::single_type_qualifier__To__precision_qualifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::storage_qualifier__To__CONST(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::storage_qualifier__To__IN(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::storage_qualifier__To__OUT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::storage_qualifier__To__INOUT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::storage_qualifier__To__UNIFORM(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier__To__type_specifier_nonarray(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier__To__type_specifier_nonarray___array_specifier(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::array_specifier__To__LM___RM(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::array_specifier__To__LM___constant_expression___RM(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::array_specifier__To__array_specifier___LM___RM(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::array_specifier__To__array_specifier___LM___constant_expression___RM(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__STRUCT__IDENTIFIER(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__VOID(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__FLOAT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__INT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__UINT(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__BOOL(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__VEC2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__VEC3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__VEC4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__BVEC2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__BVEC3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__BVEC4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__IVEC2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__IVEC3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__IVEC4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__UVEC2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__UVEC3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__UVEC4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT2X2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT2X3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT2X4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT3X2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT3X3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT3X4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT4X2(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT4X3(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__MAT4X4(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__SAMPLER2D(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__SAMPLER3D(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::type_specifier_nonarray__To__SAMPLERCUBE(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::precision_qualifier__To__HIGH_PRECISION(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::precision_qualifier__To__MEDIUM_PRECISION(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::precision_qualifier__To__LOW_PRECISION(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::initializer__To__assignment_expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::declaration_statement__To__declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::statement__To__compound_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::statement__To__simple_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::simple_statement__To__declaration_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::simple_statement__To__expression_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::simple_statement__To__selection_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::simple_statement__To__iteration_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::simple_statement__To__jump_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::compound_statement__To__LB___RB(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::compound_statement__To__LB___statement_list___RB(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::statement_list__To__statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::statement_list__To__statement_list___statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::expression_statement__To__SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::expression_statement__To__expression___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::selection_statement__To__IF___LS___expression___RS___selection_rest_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::selection_rest_statement__To__statement___ELSE___statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::selection_rest_statement__To__statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::condition__To__expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::condition__To__fully_specified_type___IDENTIFIER___EQUAL___initializer(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::iteration_statement__To__WHILE___LS___condition___RS___statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::iteration_statement__To__FOR___LS___for_init_statement___for_rest_statement___RS___statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::for_init_statement__To__expression_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::for_init_statement__To__declaration_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::condition_opt__To__condition(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::condition_opt__To__Empty(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = &_NewToken(Token::__Empty);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::for_rest_statement__To__condition_opt___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::for_rest_statement__To__condition_opt___SEMICOLON___expression(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::jump_statement__To__CONTINUE___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::jump_statement__To__BREAK___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::jump_statement__To__RETURN___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::jump_statement__To__RETURN___expression___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::jump_statement__To__DISCARD___SEMICOLON(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::translation_unit__To__external_declaration_list(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
    m_RootToken = _GetTokenId(*_);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::external_declaration_list__To__external_declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::external_declaration_list__To__external_declaration_list___external_declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::external_declaration__To__function_definition(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::external_declaration__To__declaration(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::external_declaration__To__struct_definition(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::function_definition__To__function_prototype___compound_statement(TRLSLGrammarRuleHandler::InType* _, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::struct_item__To__declaration(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    return TRLSLGrammarRuleHandler::RetType();
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::struct_item__To__LM__IDENTIFIER__RM__declaration(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    return TRLSLGrammarRuleHandler::RetType();
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::struct_item_list__To__struct_item(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    return TRLSLGrammarRuleHandler::RetType();
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::struct_item_list__To__struct_item_list__struct_item(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    return TRLSLGrammarRuleHandler::RetType();
}

TRLSLGrammarRuleHandler::RetType TRLSL_IRGenerator::struct_definition__To__STRUCT__IDENTIFIER__LB__struct_item_list__RB__SEMICOLON(TRLSLGrammarRuleHandler::InType *_, TRLSLGrammarRuleHandler::InType _1, TRLSLGrammarRuleHandler::InType _2, TRLSLGrammarRuleHandler::InType _3, TRLSLGrammarRuleHandler::InType _4, TRLSLGrammarRuleHandler::InType _5, TRLSLGrammarRuleHandler::InType _6, TRLSLGrammarRuleHandler::InType _7)
{
    return TRLSLGrammarRuleHandler::RetType();
}


} // end of namespace TRL