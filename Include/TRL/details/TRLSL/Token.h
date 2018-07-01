#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include <cstring>


namespace TRL
{


struct Token
{
    Token()
        :
        Type(0), StrLen(0), Str(nullptr), UserData(nullptr)
    {}

    Token(ToyUtility::uint16 type)
        :
        Type(type), StrLen(0), Str(nullptr), UserData(nullptr)
    {}

    Token(ToyUtility::uint16 type, const char* str);

    Token(ToyUtility::uint16 type, const char* str, int strLen)
        :
        Type(type), Str(str), StrLen(strLen), UserData(nullptr)
    {}

    // Copy constructors
    Token(const Token& t)
        : Type(t.Type), StrLen(t.StrLen), Str(t.Str), UserData(t.UserData)
    {}

    // Copy assignment operator
    Token& Token :: operator= (const Token & rhs)
    {
        Type = rhs.Type; StrLen = rhs.StrLen; Str = rhs.Str; UserData = rhs.UserData;
        return *this;
    }


public:
    void SetUserData(void* data) { UserData = data; }
    void* GetUserData() const { return UserData; }
    template<typename T>
    T* GetUserData() const { return (T*) UserData; }

    bool IsTerminalSymbol() const;


public:
    ToyUtility::uint16 Type;
    using StrLenType = ToyUtility::uint16;
    StrLenType StrLen;
    const char* Str;
    void* UserData;


    // Static Tokens
public:
    static Token __None;
    static Token __Empty;
    static Token LS;
    static Token RS;
    static Token LM;
    static Token RM;
    static Token DOT;
    static Token INC_OP;
    static Token DEC_OP;
    static Token VOID_;
    static Token COMMA;
    static Token PLUS;
    static Token DASH;
    static Token BANG;
    static Token TILDE;
    static Token STAR;
    static Token STRUCT;
    static Token SLASH;
    static Token PERCENT;
    static Token LEFT_OP;
    static Token RIGHT_OP;
    static Token LEFT_ANGLE;
    static Token RIGHT_ANGLE;
    static Token LE_OP;
    static Token GE_OP;
    static Token EQ_OP;
    static Token NE_OP;
    static Token AMPERSAND;
    static Token CARET;
    static Token VERTICAL_BAR;
    static Token AND_OP;
    static Token OR_OP;
    static Token QUESTION;
    static Token COLON;
    static Token EQUAL; // =
    static Token MUL_ASSIGN;
    static Token DIV_ASSIGN;
    static Token MOD_ASSIGN;
    static Token ADD_ASSIGN;
    static Token SUB_ASSIGN;
    static Token AND_ASSIGN;
    static Token XOR_ASSIGN;
    static Token LEFT_ASSIGN;
    static Token RIGHT_ASSIGN;
    static Token OR_ASSIGN;
    static Token SEMICOLON;
    static Token CONST_;
    static Token IN_;
    static Token OUT_;
    static Token INOUT_;
    static Token UNIFORM;
    static Token FLOAT;
    static Token INT;
    static Token UINT;
    static Token BOOL;
    static Token VEC2;
    static Token VEC3;
    static Token VEC4;
    static Token BVEC2;
    static Token BVEC3;
    static Token BVEC4;
    static Token IVEC2;
    static Token IVEC3;
    static Token IVEC4;
    static Token UVEC2;
    static Token UVEC3;
    static Token UVEC4;
    static Token MAT2;
    static Token MAT3;
    static Token MAT4;
    static Token MAT2X2;
    static Token MAT2X3;
    static Token MAT2X4;
    static Token MAT3X2;
    static Token MAT3X3;
    static Token MAT3X4;
    static Token MAT4X2;
    static Token MAT4X3;
    static Token MAT4X4;
    static Token SAMPLER2D;
    static Token SAMPLER3D;
    static Token SAMPLERCUBE;
    static Token HIGH_PRECISION;
    static Token MEDIUM_PRECISION;
    static Token LOW_PRECISION;
    static Token LB;
    static Token RB;
    static Token IF;
    static Token ELSE;
    static Token WHILE;
    static Token FOR;
    static Token CONTINUE;
    static Token BREAK;
    static Token RETURN;
    static Token DISCARD;

    static Token TRUE_;
    static Token FALSE_;
};


} // end of namespace TRL