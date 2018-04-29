#include "TRL/UniformVariable.h"


namespace TRL
{


GpuDataType UniformVariable::GetDataType() const
{
    return m_DataType;
}

const ToyUtility::String & UniformVariable::GetName() const
{
    return m_Name;
}

bool UniformVariable::IsArray() const
{
    return m_ArrayLength > 1;
}

int UniformVariable::GetArrayLength() const
{
    return m_ArrayLength;
}

int UniformVariable::GetLocation() const
{
    return m_Location;
}


} // end of namespace TRL