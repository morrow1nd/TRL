#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace TRL
{


class TRLSLTokener;
class TRLSLGenerator;


class TRLSLParser
{
public:
    bool Parse(TRLSLTokener& tokener, TRLSLGenerator& generator);


private:

};


} // end of namespace TRL