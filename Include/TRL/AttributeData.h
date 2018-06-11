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

    enum class NormalizeAction
    {
        NotNeedNormalize,
        NeedNormalize,
    };


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

    // size: Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. The initial
    //      value is 4.
    // type: Specifies the data type of each component in the array
    // stride: Specifies the byte offset between consecutive generic vertex attributes
    // beginOffset: Specifies a pointer to the first generic vertex attribute in the array (by bytes)
    void SetAttributeArray(const AttributeVariable& variable, GpuBuffer& vbo,
        GpuVariableComponentSize size, GpuDataType typeOfComponent, NormalizeAction normalizeAction, int stride, int beginOffset);
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