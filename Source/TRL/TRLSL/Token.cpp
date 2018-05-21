#include "TRL/TRLSL/Token.h"

#include <cassert>
#include <limits>
#include "TRL/TRLSL/trlsl_token_id.h"


namespace TRL
{


Token::Token(ToyUtility::uint16 type, const char* str)
    :
    Type(type), Str(str), UserData(nullptr)
{
    auto len = std::strlen(str);
    assert(len < std::numeric_limits<StrLenType>::max());
    
    StrLen = static_cast<StrLenType>(len);
}


Token Token::None = Token(0);
Token Token::LS = Token(TRLSL_T_LS, "(");
Token Token::RS = Token(TRLSL_T_RS, ")");
Token Token::LM = Token(TRLSL_T_LM, "[");
Token Token::RM = Token(TRLSL_T_RM, "]");
Token Token::DOT = Token(TRLSL_T_DOT, ".");
Token Token::INC_OP = Token(TRLSL_T_INC_OP, "++");
Token Token::DEC_OP = Token(TRLSL_T_DEC_OP, "--");
Token Token::VOID_ = Token(TRLSL_T_VOID, "void");
Token Token::COMMA = Token(TRLSL_T_COMMA, ",");
Token Token::PLUS = Token(TRLSL_T_PLUS, "+");
Token Token::DASH = Token(TRLSL_T_DASH, "-");
Token Token::BANG = Token(TRLSL_T_BANG, "!");
Token Token::TILDE = Token(TRLSL_T_TILDE, "~");
Token Token::STAR = Token(TRLSL_T_STAR, "*");
Token Token::SLASH = Token(TRLSL_T_SLASH, "/");
Token Token::PERCENT = Token(TRLSL_T_PERCENT, "%");
Token Token::LEFT_OP = Token(TRLSL_T_LEFT_OP, "<<");
Token Token::RIGHT_OP = Token(TRLSL_T_RIGHT_OP, ">>");
Token Token::LEFT_ANGLE = Token(TRLSL_T_LEFT_ANGLE, "<");
Token Token::RIGHT_ANGLE = Token(TRLSL_T_RIGHT_ANGLE, ">");
Token Token::LE_OP = Token(TRLSL_T_LE_OP, "<=");
Token Token::GE_OP = Token(TRLSL_T_GE_OP, ">=");
Token Token::EQ_OP = Token(TRLSL_T_EQ_OP, "==");
Token Token::NE_OP = Token(TRLSL_T_NE_OP, "!=");
Token Token::AMPERSAND = Token(TRLSL_T_AMPERSAND, "&");
Token Token::CARET = Token(TRLSL_T_CARET, "^");
Token Token::VERTICAL_BAR = Token(TRLSL_T_VERTICAL_BAR, "|");
Token Token::AND_OP = Token(TRLSL_T_AND_OP, "&&");
Token Token::OR_OP = Token(TRLSL_T_OR_OP, "||");
Token Token::QUESTION = Token(TRLSL_T_QUESTION, "?");
Token Token::COLON = Token(TRLSL_T_COLON, ":");
Token Token::EQUAL = Token(TRLSL_T_EQUAL, "="); // =
Token Token::MUL_ASSIGN = Token(TRLSL_T_MUL_ASSIGN, "*=");
Token Token::DIV_ASSIGN = Token(TRLSL_T_DIV_ASSIGN, "/=");
Token Token::MOD_ASSIGN = Token(TRLSL_T_MOD_ASSIGN, "%=");
Token Token::ADD_ASSIGN = Token(TRLSL_T_ADD_ASSIGN, "+=");
Token Token::SUB_ASSIGN = Token(TRLSL_T_SUB_ASSIGN, "-=");
Token Token::AND_ASSIGN = Token(TRLSL_T_AND_ASSIGN, "&=");
Token Token::XOR_ASSIGN = Token(TRLSL_T_XOR_ASSIGN, "^=");
Token Token::OR_ASSIGN = Token(TRLSL_T_OR_ASSIGN, "|=");
Token Token::LEFT_ASSIGN = Token(TRLSL_T_LEFT_ASSIGN, "<<=");
Token Token::RIGHT_ASSIGN = Token(TRLSL_T_RIGHT_ASSIGN, ">>=");
Token Token::SEMICOLON = Token(TRLSL_T_SEMICOLON, ";");
Token Token::CONST_ = Token(TRLSL_T_CONST, "const");
Token Token::IN_ = Token(TRLSL_T_IN, "in");
Token Token::OUT_ = Token(TRLSL_T_OUT, "out");
Token Token::INOUT_ = Token(TRLSL_T_INOUT, "inout");
Token Token::UNIFORM = Token(TRLSL_T_UNIFORM, "uniform");
Token Token::FLOAT = Token(TRLSL_T_FLOAT, "float");
Token Token::INT = Token(TRLSL_T_INT, "int");
Token Token::UINT = Token(TRLSL_T_UINT, "uint");
Token Token::BOOL = Token(TRLSL_T_BOOL, "bool");
Token Token::VEC2 = Token(TRLSL_T_VEC2, "vec2");
Token Token::VEC3 = Token(TRLSL_T_VEC3, "vec3");
Token Token::VEC4 = Token(TRLSL_T_VEC4, "vec4");
Token Token::BVEC2 = Token(TRLSL_T_BVEC2, "bvec2");
Token Token::BVEC3 = Token(TRLSL_T_BVEC3, "bvec3");
Token Token::BVEC4 = Token(TRLSL_T_BVEC4, "bvec4");
Token Token::IVEC2 = Token(TRLSL_T_IVEC2, "ivec2");
Token Token::IVEC3 = Token(TRLSL_T_IVEC3, "ivec3");
Token Token::IVEC4 = Token(TRLSL_T_IVEC4, "ivec4");
Token Token::UVEC2 = Token(TRLSL_T_UVEC2, "uvec2");
Token Token::UVEC3 = Token(TRLSL_T_UVEC3, "uvec3");
Token Token::UVEC4 = Token(TRLSL_T_UVEC4, "uvec4");
Token Token::MAT2 = Token(TRLSL_T_MAT2, "mat2");
Token Token::MAT3 = Token(TRLSL_T_MAT3, "mat3");
Token Token::MAT4 = Token(TRLSL_T_MAT4, "mat4");
Token Token::MAT2X2 = Token(TRLSL_T_MAT2X2, "mat2x2");
Token Token::MAT2X3 = Token(TRLSL_T_MAT2X3, "mat2x3");
Token Token::MAT2X4 = Token(TRLSL_T_MAT2X4, "mat2x4");
Token Token::MAT3X2 = Token(TRLSL_T_MAT3X2, "mat3x2");
Token Token::MAT3X3 = Token(TRLSL_T_MAT3X3, "mat3x3");
Token Token::MAT3X4 = Token(TRLSL_T_MAT3X4, "mat3x4");
Token Token::MAT4X2 = Token(TRLSL_T_MAT4X2, "mat4x2");
Token Token::MAT4X3 = Token(TRLSL_T_MAT4X3, "mat4x3");
Token Token::MAT4X4 = Token(TRLSL_T_MAT4X4, "mat4x4");
Token Token::SAMPLER2D = Token(TRLSL_T_SAMPLER2D, "sampler2D");
Token Token::SAMPLER3D = Token(TRLSL_T_SAMPLER3D, "sampler3D");
Token Token::SAMPLERCUBE = Token(TRLSL_T_SAMPLERCUBE, "samplerCube");
Token Token::HIGH_PRECISION = Token(TRLSL_T_HIGH_PRECISION, "highp");
Token Token::MEDIUM_PRECISION = Token(TRLSL_T_MEDIUM_PRECISION, "mediump");
Token Token::LOW_PRECISION = Token(TRLSL_T_LOW_PRECISION, "lowp");
Token Token::LB = Token(TRLSL_T_LB, "{");
Token Token::RB = Token(TRLSL_T_RB, "}");
Token Token::IF = Token(TRLSL_T_IF, "if");
Token Token::ELSE = Token(TRLSL_T_ELSE, "else");
Token Token::WHILE = Token(TRLSL_T_WHILE, "while");
Token Token::FOR = Token(TRLSL_T_FOR, "for");
Token Token::CONTINUE = Token(TRLSL_T_CONTINUE, "continue");
Token Token::BREAK = Token(TRLSL_T_BREAK, "break");
Token Token::RETURN = Token(TRLSL_T_RETURN, "return");
Token Token::DISCARD = Token(TRLSL_T_DISCARD, "discard");
Token Token::TRUE_ = Token(TRLSL_T_BOOLCONSTANT, "true");
Token Token::FALSE_ = Token(TRLSL_T_BOOLCONSTANT, "false");


bool Token::IsTerminalSymbol() const
{
    return Type >= 1 && Type <= TRLSL_T_DISCARD; // TODOL: has a better way ?
}


} // end of namespace TRL