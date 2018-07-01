#include "TRL/details/TRLSL/GLSLGenerator.h"

#include <sstream>
#include "ToyUtility/DataStream/DataStream.h"


namespace TRL
{


Token* GLSLGenerator::NextToken(bool restart)
{
    if(restart)
        m_CurrToken = 0;

    if (m_CurrToken < (int) m_Tokens.size())
    {
        return (Token*)&m_TokenPool[m_Tokens[m_CurrToken++]];
    }

    return nullptr;
}

void GLSLGenerator::SetAllTokens(const ToyUtility::List<Token>& tokens)
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

void GLSLGenerator::GenerateCode(ToyUtility::DataStream& stream) const
{
    stream.WriteString("#version 330 core\n");

    for (size_t tokenIndex = m_RootToken; tokenIndex != 0 && tokenIndex < m_TokenPool.size(); )
    {
        const Token& t = m_TokenPool[tokenIndex];
        size_t thIndex = (size_t)t.GetUserData();
        // TODOL: check thIndex range
        const TokenHelper& th = m_TokenHelpers[thIndex];

        if (t.IsTerminalSymbol())
        {
            stream.Write(t.Str, t.StrLen);
            stream.Write(" ", 1);
        }

        tokenIndex = th.Next;
    }
}

ToyUtility::String GLSLGenerator::GenerateCode() const
{
    std::stringstream stream;

    // TODOM: I don't write the same code twice
    stream << "#version 330 core\n";

    for (size_t tokenIndex = m_RootToken; tokenIndex != 0 && tokenIndex < m_TokenPool.size(); )
    {
        const Token& t = m_TokenPool[tokenIndex];
        size_t thIndex = (size_t)t.GetUserData();
        // TODOL: check thIndex range
        const TokenHelper& th = m_TokenHelpers[thIndex];

        if (t.IsTerminalSymbol())
        {
            stream.write(t.Str, t.StrLen);
            stream.write(" ", 1);
        }

        tokenIndex = th.Next;
    }

    return stream.str();
}

Token * GLSLGenerator::_GetLastOne(Token * t)
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

int GLSLGenerator::_GetLastOneId(Token * t)
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

void GLSLGenerator::_LinkTokens(Token * _1, Token * _2, Token * _3, Token * _4, Token * _5, Token * _6, Token * _7)
{
    auto th = _GetTokenHelper(_1);

    Token* end = nullptr;

    if (_2 != nullptr) { _LinkTokens(_1, _2); end = _2; }
    if (_3 != nullptr) { _LinkTokens(_2, _3); end = _3; }
    if (_4 != nullptr) { _LinkTokens(_3, _4); end = _4; }
    if (_5 != nullptr) { _LinkTokens(_4, _5); end = _5; }
    if (_6 != nullptr) { _LinkTokens(_5, _6); end = _6; }
    if (_7 != nullptr) { _LinkTokens(_6, _7); end = _7; }

    if (end != nullptr)
    {
        th->Last = _GetTokenId(_GetLastOne(end));
    }
}

void GLSLGenerator::_LinkTokens(Token* a, Token* b)
{
    if(a == nullptr)
        return;

    auto last = _GetLastOne(a);
    _GetTokenHelper(last)->Next = _GetTokenId(b);
    _GetTokenHelper(a)->Last = _GetLastOneId(b);
}

Token& GLSLGenerator::_NewToken(Token t)
{
    m_TokenHelpers.push_back(TokenHelper());
    m_TokenPool.push_back(t);
    m_TokenPool.back().SetUserData((void*)(m_TokenHelpers.size() - 1));
    m_TokenHelpers.back().TokenIndex = m_TokenPool.size() - 1;
    return m_TokenPool.back();
}

// TODOL: Remove unused arguments
TRLSLGenerator::RetType GLSLGenerator::variable_identifier__To__IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::primary_expression__To__variable_identifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::primary_expression__To__INTCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::primary_expression__To__UINTCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::primary_expression__To__FLOATCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::primary_expression__To__BOOLCONSTANT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::primary_expression__To__LS___expression___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::postfix_expression__To__primary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::postfix_expression__To__postfix_expression___LM___integer_expression___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::postfix_expression__To__function_call(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::postfix_expression__To__postfix_expression___DOT___FIELD_SELECTION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::postfix_expression__To__postfix_expression___INC_OP(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::postfix_expression__To__postfix_expression___DEC_OP(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::integer_expression__To__expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call__To__function_call_or_method(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_or_method__To__function_call_generic(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_generic__To__function_call_header_with_parameters___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_generic__To__function_call_header_no_parameters___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_header_no_parameters__To__function_call_header___VOID(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_header_no_parameters__To__function_call_header(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_header_with_parameters__To__function_call_header___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_header_with_parameters__To__function_call_header_with_parameters___COMMA___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_call_header__To__function_identifier___LS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_identifier__To__type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_identifier__To__postfix_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_expression__To__postfix_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_expression__To__INC_OP___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_expression__To__DEC_OP___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_expression__To__unary_operator___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_operator__To__PLUS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_operator__To__DASH(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_operator__To__BANG(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::unary_operator__To__TILDE(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::multiplicative_expression__To__unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::multiplicative_expression__To__multiplicative_expression___STAR___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::multiplicative_expression__To__multiplicative_expression___SLASH___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::multiplicative_expression__To__multiplicative_expression___PERCENT___unary_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::additive_expression__To__multiplicative_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::additive_expression__To__additive_expression___PLUS___multiplicative_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::additive_expression__To__additive_expression___DASH___multiplicative_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::shift_expression__To__additive_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::shift_expression__To__shift_expression___LEFT_OP___additive_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::shift_expression__To__shift_expression___RIGHT_OP___additive_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::relational_expression__To__shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::relational_expression__To__relational_expression___LEFT_ANGLE___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::relational_expression__To__relational_expression___RIGHT_ANGLE___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::relational_expression__To__relational_expression___LE_OP___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::relational_expression__To__relational_expression___GE_OP___shift_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::equality_expression__To__relational_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::equality_expression__To__equality_expression___EQ_OP___relational_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::equality_expression__To__equality_expression___NE_OP___relational_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::and_expression__To__equality_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::and_expression__To__and_expression___AMPERSAND___equality_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::exclusive_or_expression__To__and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::exclusive_or_expression__To__exclusive_or_expression___CARET___and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::inclusive_or_expression__To__exclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::inclusive_or_expression__To__inclusive_or_expression___VERTICAL_BAR___exclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::logical_and_expression__To__inclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::logical_and_expression__To__logical_and_expression___AND_OP___inclusive_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::logical_or_expression__To__logical_and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::logical_or_expression__To__logical_or_expression___OR_OP___logical_and_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::conditional_expression__To__logical_or_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::conditional_expression__To__logical_or_expression___QUESTION___expression___COLON___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_expression__To__conditional_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_expression__To__unary_expression___assignment_operator___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__EQUAL(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__MUL_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__DIV_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__MOD_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__ADD_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__SUB_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__LEFT_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__RIGHT_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__AND_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__XOR_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::assignment_operator__To__OR_ASSIGN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::expression__To__assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::expression__To__expression___COMMA___assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::constant_expression__To__conditional_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::declaration__To__init_declarator_list___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_prototype__To__function_declarator___RS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_declarator__To__function_header(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_declarator__To__function_header_with_parameters(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_header_with_parameters__To__function_header___parameter_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_header_with_parameters__To__function_header_with_parameters___COMMA___parameter_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_header__To__fully_specified_type___IDENTIFIER___LS(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_declarator__To__type_specifier___IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_declarator__To__type_specifier___IDENTIFIER___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_declaration__To__type_qualifier___parameter_declarator(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_declaration__To__parameter_declarator(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_declaration__To__type_qualifier___parameter_type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_declaration__To__parameter_type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::parameter_type_specifier__To__type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::init_declarator_list__To__single_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_declaration__To__fully_specified_type(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_declaration__To__fully_specified_type___IDENTIFIER___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::fully_specified_type__To__type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::fully_specified_type__To__type_qualifier___type_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_qualifier__To__single_type_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_qualifier__To__type_qualifier___single_type_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_type_qualifier__To__storage_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::single_type_qualifier__To__precision_qualifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::storage_qualifier__To__CONST(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::storage_qualifier__To__IN(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::storage_qualifier__To__OUT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::storage_qualifier__To__INOUT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::storage_qualifier__To__UNIFORM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier__To__type_specifier_nonarray(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier__To__type_specifier_nonarray___array_specifier(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::array_specifier__To__LM___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::array_specifier__To__LM___constant_expression___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::array_specifier__To__array_specifier___LM___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::array_specifier__To__array_specifier___LM___constant_expression___RM(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRL::TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__STRUCT__IDENTIFIER(TRL::TRLSLGenerator::InType *_, TRL::TRLSLGenerator::InType _1, TRL::TRLSLGenerator::InType _2, TRL::TRLSLGenerator::InType _3, TRL::TRLSLGenerator::InType _4, TRL::TRLSLGenerator::InType _5, TRL::TRLSLGenerator::InType _6, TRL::TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__VOID(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__FLOAT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__INT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__UINT(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__BOOL(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__VEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__VEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__VEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__BVEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__BVEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__BVEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__IVEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__IVEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__IVEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__UVEC2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__UVEC3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__UVEC4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT2X2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT2X3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT2X4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT3X2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT3X3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT3X4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT4X2(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT4X3(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__MAT4X4(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__SAMPLER2D(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__SAMPLER3D(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::type_specifier_nonarray__To__SAMPLERCUBE(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::precision_qualifier__To__HIGH_PRECISION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::precision_qualifier__To__MEDIUM_PRECISION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::precision_qualifier__To__LOW_PRECISION(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::initializer__To__assignment_expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::declaration_statement__To__declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::statement__To__compound_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::statement__To__simple_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::simple_statement__To__declaration_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::simple_statement__To__expression_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::simple_statement__To__selection_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::simple_statement__To__iteration_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::simple_statement__To__jump_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::compound_statement__To__LB___RB(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::compound_statement__To__LB___statement_list___RB(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::statement_list__To__statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::statement_list__To__statement_list___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::expression_statement__To__SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::expression_statement__To__expression___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::selection_statement__To__IF___LS___expression___RS___selection_rest_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::selection_rest_statement__To__statement___ELSE___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::selection_rest_statement__To__statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::condition__To__expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::condition__To__fully_specified_type___IDENTIFIER___EQUAL___initializer(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::iteration_statement__To__WHILE___LS___condition___RS___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::iteration_statement__To__FOR___LS___for_init_statement___for_rest_statement___RS___statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::for_init_statement__To__expression_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::for_init_statement__To__declaration_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::condition_opt__To__condition(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::condition_opt__To__Empty(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = &_NewToken(Token::__Empty);
}

TRLSLGenerator::RetType GLSLGenerator::for_rest_statement__To__condition_opt___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::for_rest_statement__To__condition_opt___SEMICOLON___expression(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::jump_statement__To__CONTINUE___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::jump_statement__To__BREAK___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::jump_statement__To__RETURN___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::jump_statement__To__RETURN___expression___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::jump_statement__To__DISCARD___SEMICOLON(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::translation_unit__To__external_declaration_list(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
    m_RootToken = _GetTokenId(*_);
}

TRLSLGenerator::RetType GLSLGenerator::external_declaration_list__To__external_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::external_declaration_list__To__external_declaration_list___external_declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::external_declaration__To__function_definition(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::external_declaration__To__declaration(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::external_declaration__To__struct_definition(TRLSLGenerator::InType *_, TRL::TRLSLGenerator::InType _1, TRL::TRLSLGenerator::InType _2, TRL::TRLSLGenerator::InType _3, TRL::TRLSLGenerator::InType _4, TRL::TRLSLGenerator::InType _5, TRL::TRLSLGenerator::InType _6, TRL::TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRLSLGenerator::RetType GLSLGenerator::function_definition__To__function_prototype___compound_statement(TRLSLGenerator::InType* _, TRLSLGenerator::InType _1, TRLSLGenerator::InType _2, TRLSLGenerator::InType _3, TRLSLGenerator::InType _4, TRLSLGenerator::InType _5, TRLSLGenerator::InType _6, TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRL::TRLSLGenerator::RetType GLSLGenerator::declaration_list__To__declaration(TRL::TRLSLGenerator::InType *_, TRL::TRLSLGenerator::InType _1, TRL::TRLSLGenerator::InType _2, TRL::TRLSLGenerator::InType _3, TRL::TRLSLGenerator::InType _4, TRL::TRLSLGenerator::InType _5, TRL::TRLSLGenerator::InType _6, TRL::TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRL::TRLSLGenerator::RetType GLSLGenerator::declaration_list__To__declaration_list__declaration(TRL::TRLSLGenerator::InType *_, TRL::TRLSLGenerator::InType _1, TRL::TRLSLGenerator::InType _2, TRL::TRLSLGenerator::InType _3, TRL::TRLSLGenerator::InType _4, TRL::TRLSLGenerator::InType _5, TRL::TRLSLGenerator::InType _6, TRL::TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}

TRL::TRLSLGenerator::RetType GLSLGenerator::struct_definition__To__STRUCT__IDENTIFIER__LB__declaration_list__RB__SEMICOLON(TRL::TRLSLGenerator::InType *_, TRL::TRLSLGenerator::InType _1, TRL::TRLSLGenerator::InType _2, TRL::TRLSLGenerator::InType _3, TRL::TRLSLGenerator::InType _4, TRL::TRLSLGenerator::InType _5, TRL::TRLSLGenerator::InType _6, TRL::TRLSLGenerator::InType _7)
{
    *_ = _1;
    _LinkTokens(_1, _2, _3, _4, _5, _6, _7);
}


} // end of namespace TRL