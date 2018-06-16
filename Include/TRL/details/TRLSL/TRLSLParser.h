#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace TRL
{


class TRLSLTokener;
class TRLSLGenerator;


class TRLSLParser
{
public:
    TRLSLParser(TRLSLGenerator& generator);
    ~TRLSLParser();

    bool Parse(TRLSLTokener& tokener);


private:
    TRLSLGenerator& m_Generator;
    void* m_InnerParser;
};


} // end of namespace TRL