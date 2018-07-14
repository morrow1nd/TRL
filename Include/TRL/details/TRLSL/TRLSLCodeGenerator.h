#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DataStream/DataStream.h"
#include "TRL/details/TRLSL/TRLSL_IR.h"


namespace TRL
{

// Interface: Code generator for every native shader language
class TRLSLCodeGenerator
{
public:
    virtual ~TRLSLCodeGenerator() = default;


public:
    virtual void GenerateCode(TRLSL_IR& ir, ToyUtility::DataStream& stream) = 0;
};


} // end of namespace TRL