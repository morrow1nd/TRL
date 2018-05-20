#include "TRL/TRLSL/TRLSLTokener.h"

#include <cstring>
#include <cctype>
#include "TRL/TRLSL/trlsl_token_id.h"


namespace TRL
{


bool TRLSLTokener::Prepare(ToyUtility::DataStream & inputStream)
{
    m_Input = inputStream.GetAsString();
    m_Begin = m_Input.c_str();
    m_Length = m_Input.size();

    return _ScanAll();
}

const Token& TRLSLTokener::NextToken()
{
    if(m_CurrToken >= m_Tokens.size())
        return Token::None;

    return m_Tokens[m_CurrToken++];
}

#define CMP_WITH_TOKEN(StrPtr, TokenName) \
_StrCmp((StrPtr), Token::TokenName.Str, Token::TokenName.StrLen)

#define PUSH_TOKEN(TokenName) \
{ \
    m_Tokens.push_back(Token::TokenName); \
    i += Token::TokenName.StrLen; \
}

#define CHECK_PUSH_BREAK(StrPtr, TokenName) \
{ \
    if(CMP_WITH_TOKEN(StrPtr, TokenName)) /* 1. Check */ \
    { \
        PUSH_TOKEN(TokenName); /* 2. Push */ \
        break; /* 3. Break */ \
    } \
}

bool TRLSLTokener::_ScanAll()
{
    int i = 0;
    const char* c;

    while (i < m_Length)
    {
        i = _ConsumeSpace(i);

        c = m_Begin + i;

        switch (*c)
        {
        case 'b':
            CHECK_PUSH_BREAK(c, BOOL);
            CHECK_PUSH_BREAK(c, BREAK);
            _CheckIdentifier(c, &i);
            break;
        case 'c':
            CHECK_PUSH_BREAK(c, CONST_);
            CHECK_PUSH_BREAK(c, CONTINUE);
            _CheckIdentifier(c, &i);
            break;
        case 'd':
            CHECK_PUSH_BREAK(c, DISCARD);
            _CheckIdentifier(c, &i);
            break;
        case 'e':
            CHECK_PUSH_BREAK(c, ELSE);
            _CheckIdentifier(c, &i);
            break;
        case 'f':
            CHECK_PUSH_BREAK(c, FLOAT);
            CHECK_PUSH_BREAK(c, FOR);
            CHECK_PUSH_BREAK(c, FALSE_);
            _CheckIdentifier(c, &i);
            break;
        case 'h':
            CHECK_PUSH_BREAK(c, HIGH_PRECISION);
            _CheckIdentifier(c, &i);
            break;
        case 'i':
            //CHECK_PUSH_BREAK(c, IDENTIFIER);
            CHECK_PUSH_BREAK(c, IF);
            CHECK_PUSH_BREAK(c, INT);
            CHECK_PUSH_BREAK(c, INOUT_);
            CHECK_PUSH_BREAK(c, IN_);
            CHECK_PUSH_BREAK(c, IVEC2);
            CHECK_PUSH_BREAK(c, IVEC3);
            CHECK_PUSH_BREAK(c, IVEC4);
            _CheckIdentifier(c, &i);
            break;
        case 'l':
            CHECK_PUSH_BREAK(c, LOW_PRECISION);
            _CheckIdentifier(c, &i);
            break;
        case 'm':
            CHECK_PUSH_BREAK(c, MEDIUM_PRECISION);
            CHECK_PUSH_BREAK(c, MAT2);
            CHECK_PUSH_BREAK(c, MAT3);
            CHECK_PUSH_BREAK(c, MAT4);
            CHECK_PUSH_BREAK(c, MAT2X2);
            CHECK_PUSH_BREAK(c, MAT2X3);
            CHECK_PUSH_BREAK(c, MAT2X4);
            CHECK_PUSH_BREAK(c, MAT3X2);
            CHECK_PUSH_BREAK(c, MAT3X3);
            CHECK_PUSH_BREAK(c, MAT3X4);
            CHECK_PUSH_BREAK(c, MAT4X2);
            CHECK_PUSH_BREAK(c, MAT4X3);
            CHECK_PUSH_BREAK(c, MAT4X4);
            _CheckIdentifier(c, &i);
            break;
        case 'o':
            CHECK_PUSH_BREAK(c, OUT_);
            _CheckIdentifier(c, &i);
            break;
        case 'r':
            CHECK_PUSH_BREAK(c, RETURN);
            _CheckIdentifier(c, &i);
            break;
        case 's':
            CHECK_PUSH_BREAK(c, SAMPLER2D);
            CHECK_PUSH_BREAK(c, SAMPLER3D);
            CHECK_PUSH_BREAK(c, SAMPLERCUBE);
            _CheckIdentifier(c, &i);
            break;
        case 't':
            CHECK_PUSH_BREAK(c, TRUE_);
            _CheckIdentifier(c, &i);
            break;
        case 'u':
            CHECK_PUSH_BREAK(c, UNIFORM);
            CHECK_PUSH_BREAK(c, UINT);
            CHECK_PUSH_BREAK(c, UVEC2);
            CHECK_PUSH_BREAK(c, UVEC3);
            CHECK_PUSH_BREAK(c, UVEC4);
            _CheckIdentifier(c, &i);
            break;
        case 'v':
            CHECK_PUSH_BREAK(c, VEC2);
            CHECK_PUSH_BREAK(c, VEC3);
            CHECK_PUSH_BREAK(c, VEC4);
            CHECK_PUSH_BREAK(c, VOID_);
            _CheckIdentifier(c, &i);
            break;
        case 'w':
            CHECK_PUSH_BREAK(c, WHILE);
            _CheckIdentifier(c, &i);
            break;
        case '+':
            CHECK_PUSH_BREAK(c, INC_OP);
            CHECK_PUSH_BREAK(c, ADD_ASSIGN);
            CHECK_PUSH_BREAK(c, PLUS);
            break;
        case '-':
            CHECK_PUSH_BREAK(c, DEC_OP); // --
            CHECK_PUSH_BREAK(c, SUB_ASSIGN); // -=

            if (_CheckFirstTokenForDash())
            {
                // nagative number
                char* numberEnd;
                auto num = strtod(c, &numberEnd);
                if (numberEnd == c)
                {
                    m_Error.ErrorInfo = "uninvalid number found at pos: "
                        + std::to_string(c - m_Begin)
                        + "\n" + ToyUtility::String(c);
                    return false;
                }
                else
                {
                    // TODOH
                    m_Tokens.push_back(Token(TRLSL_T_FLOATCONSTANT, c, numberEnd - c));
                    i += (numberEnd - m_Begin);
                }
            }
            else
            {
                // Sub Operator
                CHECK_PUSH_BREAK(c, DASH);
            }

            break;
        case '*':
            CHECK_PUSH_BREAK(c, MUL_ASSIGN);
            CHECK_PUSH_BREAK(c, STAR);
            break;
        case '/':
            CHECK_PUSH_BREAK(c, DIV_ASSIGN);
            CHECK_PUSH_BREAK(c, SLASH);
            break;
        case '<':
            CHECK_PUSH_BREAK(c, LEFT_ASSIGN);
            CHECK_PUSH_BREAK(c, LEFT_OP);
            CHECK_PUSH_BREAK(c, LE_OP);
            CHECK_PUSH_BREAK(c, LEFT_ANGLE);
            break;
        case '>':
            CHECK_PUSH_BREAK(c, RIGHT_ASSIGN);
            CHECK_PUSH_BREAK(c, RIGHT_OP);
            CHECK_PUSH_BREAK(c, GE_OP);
            CHECK_PUSH_BREAK(c, RIGHT_ANGLE);
            break;
        case '=':
            CHECK_PUSH_BREAK(c, EQ_OP);
            CHECK_PUSH_BREAK(c, EQUAL);
            break;
        case '!':
            CHECK_PUSH_BREAK(c, NE_OP);
            CHECK_PUSH_BREAK(c, BANG);
            break;
        case '&':
            CHECK_PUSH_BREAK(c, AND_OP);
            CHECK_PUSH_BREAK(c, AND_ASSIGN);
            CHECK_PUSH_BREAK(c, AMPERSAND);
            break;
        case '%':
            CHECK_PUSH_BREAK(c, MOD_ASSIGN);
            CHECK_PUSH_BREAK(c, PERCENT);
            break;
        case '|':
            CHECK_PUSH_BREAK(c, OR_OP);
            CHECK_PUSH_BREAK(c, OR_ASSIGN);
            CHECK_PUSH_BREAK(c, VERTICAL_BAR);
            break;
        case '^':
            CHECK_PUSH_BREAK(c, XOR_ASSIGN);
            CHECK_PUSH_BREAK(c, CARET);
            break;
        case '.':
            CHECK_PUSH_BREAK(c, DOT);
            break;
        case ',':
            CHECK_PUSH_BREAK(c, COMMA);
            break;
        case '?':
            CHECK_PUSH_BREAK(c, QUESTION);
            break;
        case ':':
            CHECK_PUSH_BREAK(c, COLON);
            break;
        case ';':
            CHECK_PUSH_BREAK(c, SEMICOLON);
            break;
        case '(':
            CHECK_PUSH_BREAK(c, LS);
            break;
        case ')':
            CHECK_PUSH_BREAK(c, RS);
            break;
        case '[':
            CHECK_PUSH_BREAK(c, LM);
            break;
        case ']':
            CHECK_PUSH_BREAK(c, RM);
            break;
        case '{':
            CHECK_PUSH_BREAK(c, LB);
            break;
        case '}':
            CHECK_PUSH_BREAK(c, RB);
            break;
        default:
            if (std::isalpha(*c) || *c == '_')
            {
                _CheckIdentifier(c, &i);
            }
            else if (std::isdigit(*c))
            {
                char* numberEnd;
                auto num = strtod(c, &numberEnd);
                if (numberEnd == c)
                {
                    m_Error.ErrorInfo = "uninvalid number found at pos: "
                        + std::to_string(c - m_Begin)
                        + "\n" + ToyUtility::String(c);
                    return false;
                }
                else
                {
                    // TODOH
                    m_Tokens.push_back(Token(TRLSL_T_FLOATCONSTANT, c, numberEnd - c));
                    i = numberEnd - m_Begin;
                }
            }
            break;
        }
    }

    return true; // Success
}

int TRLSLTokener::_ConsumeSpace(int i) const
{
    while (i < m_Length
        && (isspace(*(m_Begin + i))
            || iscntrl(*(m_Begin + i))
            || isblank(*(m_Begin + i))
            )
        )
    {
        ++i;
    }
    return i;
}

bool TRLSLTokener::_StrCmp(const char * str1, const char * str2, int length) const
{
    return memcmp(str1, str2, length) == 0;
}

bool TRLSLTokener::_LastTokenIsNumber() const
{
    if(m_Tokens.empty())
        return false;

    auto t = m_Tokens.back().Type;

    return t == TRLSL_T_INTCONSTANT
        || t == TRLSL_T_UINTCONSTANT
        || t == TRLSL_T_FLOATCONSTANT;
}

bool TRLSLTokener::_CheckFirstTokenForDash() const
{
    if (m_Tokens.empty())
        return true;

    auto t = m_Tokens.back().Type;

    // TODOM: use if( t >= .. && t <= ..), for this macro is relative
    return t == TRLSL_T_COMMA
        || t == TRLSL_T_PLUS
        || t == TRLSL_T_DASH
        || t == TRLSL_T_BANG
        || t == TRLSL_T_TILDE
        || t == TRLSL_T_STAR
        || t == TRLSL_T_SLASH
        || t == TRLSL_T_PERCENT
        || t == TRLSL_T_LEFT_OP
        || t == TRLSL_T_RIGHT_OP
        || t == TRLSL_T_LEFT_ANGLE
        || t == TRLSL_T_RIGHT_ANGLE
        || t == TRLSL_T_LE_OP
        || t == TRLSL_T_GE_OP
        || t == TRLSL_T_EQ_OP
        || t == TRLSL_T_NE_OP
        || t == TRLSL_T_AMPERSAND
        || t == TRLSL_T_CARET
        || t == TRLSL_T_VERTICAL_BAR
        || t == TRLSL_T_AND_OP
        || t == TRLSL_T_OR_OP
        || t == TRLSL_T_QUESTION
        || t == TRLSL_T_COLON
        || t == TRLSL_T_EQUAL
        || t == TRLSL_T_MUL_ASSIGN
        || t == TRLSL_T_DIV_ASSIGN
        || t == TRLSL_T_MOD_ASSIGN
        || t == TRLSL_T_ADD_ASSIGN
        || t == TRLSL_T_SUB_ASSIGN
        || t == TRLSL_T_LEFT_ASSIGN
        || t == TRLSL_T_RIGHT_ASSIGN
        || t == TRLSL_T_AND_ASSIGN
        || t == TRLSL_T_XOR_ASSIGN
        || t == TRLSL_T_OR_ASSIGN
        || t == TRLSL_T_SEMICOLON
        || t == TRLSL_T_LS
        || t == TRLSL_T_LM
        || t == TRLSL_T_RETURN
        ;
}

void TRLSLTokener::_CheckIdentifier(const char* c, int* i)
{
    const char* begin = c;

    c += 1;
    while (c - m_Begin < m_Length
        && (isalpha(*c) || *c == '_' || isdigit(*c)))
    {
        c++;
    }

    if (!m_Tokens.empty() && m_Tokens.back().Type == TRLSL_T_DOT)
    {
        m_Tokens.push_back(Token(TRLSL_T_FIELD_SELECTION, begin, c - begin));
    }
    else
    {
        m_Tokens.push_back(Token(TRLSL_T_IDENTIFIER, begin, c - begin));
    }

    *i = c - m_Begin;
}


} // end of namespace TRL