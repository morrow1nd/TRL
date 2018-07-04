#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace TRL
{


class TRLSLTokener;
class TRLCodeGenerator;


class TRLSLParser
{
public:
    TRLSLParser(TRLSLTokener& tokener);
    ~TRLSLParser();


private:
    void* m_InnerParser; // lemon parser
};


} // end of namespace TRL