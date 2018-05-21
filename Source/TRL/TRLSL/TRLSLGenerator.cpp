#include "TRL/TRLSL/TRLSLGenerator.h"

#include <exception>


namespace TRL
{


ToyUtility::List<Token>& TRLSLGenerator::GetInnerTokenPool()
{
    throw std::exception("TRLSLGenerator::GetInnerTokenPool: you should impl this virtual function.");
}


} // end of namespace TRL