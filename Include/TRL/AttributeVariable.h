#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "TRL/TRLCommonType.h"


namespace TRL
{


class AttributeVariable
{
public:
    static AttributeVariable None;


public:
    AttributeVariable()
        :
        m_Location(0),
        m_DataType(GPU_DATA_TYPE_INIT),
        m_ArrayLength(0)
    {}

    AttributeVariable(const ToyUtility::String& name, int location, GpuDataType type, int arrayLength)
        :
        m_Name(name),
        m_Location(location),
        m_DataType(type),
        m_ArrayLength(arrayLength)
    {}

    bool operator==(const AttributeVariable& rhs) const
    {
        return m_Location == rhs.m_Location
            && m_ArrayLength == rhs.m_ArrayLength
            && m_DataType == rhs.m_DataType
            && m_Name == rhs.m_Name;
    }


public:
    GpuDataType GetDataType() const;
    const ToyUtility::String& GetName() const;
    bool IsArray() const;
    int GetArrayLength() const;
    int GetLocation() const;


private:
    ToyUtility::String m_Name;
    int m_Location; // layout
    GpuDataType m_DataType;
    int m_ArrayLength;
};


} // end of namespace TRL