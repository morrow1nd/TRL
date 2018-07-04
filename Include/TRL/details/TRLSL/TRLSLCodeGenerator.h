#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DataStream/DataStream.h"
#include "TRL/TRLShader.h"


namespace TRL
{


class TRLSLCodeGenerator
{
public:
    virtual ~TRLSLCodeGenerator() = default;


public:
    virtual void GenerateCode(ToyUtility::DataStream& stream) = 0;
    virtual ToyUtility::SPtr<TRLShader> GenerateCode() = 0;
};


} // end of namespace TRL