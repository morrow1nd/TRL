#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DataStream/DataStream.h"
#include "ToyUtility/String/String.h"
#include "ToyUtility/Container/List.h"
#include "TRL/TRLCommonType.h"
#include "TRL/TRLSL/Token.h"


namespace TRL
{


class TRLSLTokenerError
{
public:
    TRLSLTokenerError(){}

    TRLSLTokenerError(ToyUtility::uint32 errorType, const ToyUtility::String& errorInfo)
        : ErrorType(errorType), ErrorInfo(errorInfo)
    {}


public:
    static TRLSLTokenerError EOFCharFoundInText;


public:
    ToyUtility::uint32 ErrorType;
    ToyUtility::String ErrorInfo;
};


class TRLSLTokener
{
public:
    TRLSLTokener()
        :
        m_Begin(nullptr),
        m_BinaryDataSize(0),
        m_CurrToken(0)
    {}


public:
    bool Prepare(ToyUtility::DataStream& inputStream);
    bool Prepare(const ToyUtility::String& inputCode);

    const Token& NextToken();
    void CopyAllTokens(ToyUtility::List<Token>& container) const;
    const ToyUtility::List<Token>& GetAllTokens() const { return m_Tokens; }

    const TRLSLTokenerError& GetError() const { return m_Error; }


private:
    bool _ScanAll();

    inline int _ConsumeSpace(int i) const;

    bool _StrCmp(const char* str1, const char* str2, int length) const;

    bool _LastTokenIsNumber() const;
    bool _CheckFirstTokenForDash() const;

    void _CheckIdentifier(const char* c, int* i);


private:
    ToyUtility::String m_Input;
    const char* m_Begin;
    int m_BinaryDataSize;
    ToyUtility::List<Token> m_Tokens;
    unsigned int m_CurrToken;
    TRLSLTokenerError m_Error;
};


} // end of namespace TRL