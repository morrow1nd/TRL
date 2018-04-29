#include "TRL/AttributeVariable.h"


namespace TRL
{


AttributeVariable AttributeVariable::None = AttributeVariable();


GpuDataType AttributeVariable::GetDataType() const
{
    return m_DataType;
}

const ToyUtility::String & AttributeVariable::GetName() const
{
    return m_Name;
}

bool AttributeVariable::IsArray() const
{
    return m_ArrayLength > 1;
}

int AttributeVariable::GetArrayLength() const
{
    return m_ArrayLength;
}

int AttributeVariable::GetLocation() const
{
    return m_Location;
}

} // end of namespace TRL