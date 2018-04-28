#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuBuffer;
class AttributeVariable;


class AttributeData
{
public:
    static int GetMaxAttributeNumber();


public:
    AttributeData()
        :
        m_VAO(0)
    { }


public:
    void Init();
    void Active();
    void Inactive();

    void SetIndicesBuffer(const GpuBuffer& ebo, int indicesNumber, GpuDataType type);
    int GetIndicesNumber() const;
    GpuDataType GetIndicesDataType() const;

    void SetAttributeArray(const AttributeVariable& variable, GpuBuffer& vbo,
        int size, GpuDataType type, bool normalized, int stride, int begin_offset);
    void EnableAttributeArray(const AttributeVariable& variable, bool enable);
    void SetConstantAttribute(const AttributeVariable& variable, GpuFloat x);
    void SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y);
    void SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z);
    void SetConstantAttribute(const AttributeVariable& variable,
        GpuFloat x, GpuFloat y, GpuFloat z, GpuFloat w);
    void SetConstantAttribute(const AttributeVariable& variable, GpuInt x, GpuInt y, GpuInt z, GpuInt w);
    void SetConstantAttribute(const AttributeVariable& variable, GpuUInt x, GpuUInt y, GpuUInt z, GpuUInt w);
    // Argument /size/ can be 1, 2, 3, 4
    void SetConstantAttribute(const AttributeVariable& variable, int size, const GpuFloat* values);
    // Argument values should has 4 elements
    void SetConstantAttribute(const AttributeVariable& variable, const GpuInt* values);
    // Argument values should has 4 elements
    void SetConstantAttribute(const AttributeVariable& variable, const GpuUInt* values);

    void Destory();


private:
    struct EBOInfo
    {
        EBOInfo()
            :
            IndicesNumber(0),
            DataType(GPU_DATA_TYPE_INIT)
        {}

        int IndicesNumber;
        GpuDataType DataType;
    };

private:
    GpuVAOInner m_VAO;
    EBOInfo m_EBOInfo;
};


} // end of namespace TRL