#include "TRL/AttributeData.h"
#include "TRL/GpuBuffer.h"
#include "TRL/AttributeVariable.h"


namespace TRL
{


void AttributeData::Init()
{
    glGenVertexArrays(1, &m_VAO);
}

void AttributeData::Active()
{
    glBindVertexArray(m_VAO);
}

void AttributeData::Inactive()
{
    glBindVertexArray(0);
}

void AttributeData::SetIndicesBuffer(const GpuBuffer& ebo, int indicesNumber, GpuDataType type)
{
    ebo.Bind();
    m_EBOInfo.DataType = type;
    m_EBOInfo.IndicesNumber = indicesNumber;
}

int AttributeData::GetIndicesNumber() const
{
    return m_EBOInfo.IndicesNumber;
}

GpuDataType AttributeData::GetIndicesDataType() const
{
    return m_EBOInfo.DataType;
}

void AttributeData::SetAttributeArray(const AttributeVariable& variable, GpuBuffer& vbo,
    int size, GpuDataType type, bool normalized, int stride, int begin_offset)
{
    vbo.Bind();
    glEnableVertexAttribArray(variable.m_Layout);
    glVertexAttribPointer(variable.m_Layout, size, type, normalized, stride, (const void*)begin_offset);
}

void AttributeData::EnableAttributeArray(const AttributeVariable& variable, bool enable)
{
    if (enable)
        glEnableVertexAttribArray(variable.m_Layout);
    else
        glDisableVertexAttribArray(variable.m_Layout);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x)
{
    glVertexAttrib1f(variable.m_Layout, x);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y)
{
    glVertexAttrib2f(variable.m_Layout, x, y);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z)
{
    glVertexAttrib3f(variable.m_Layout, x, y, z);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z, GpuFloat w)
{
    glVertexAttrib4f(variable.m_Layout, x, y, z, w);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuInt x, GpuInt y, GpuInt z, GpuInt w)
{
    glVertexAttribI4i(variable.m_Layout, x, y, z, w);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuUInt x, GpuUInt y, GpuUInt z, GpuUInt w)
{
    glVertexAttribI4ui(variable.m_Layout, x, y, z, w);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, int size, const GpuFloat * values)
{
    switch (size)
    {
    case 1:
        glVertexAttrib1fv(variable.m_Layout, values);
        break;
    case 2:
        glVertexAttrib2fv(variable.m_Layout, values);
        break;
    case 3:
        glVertexAttrib3fv(variable.m_Layout, values);
        break;
    case 4:
        glVertexAttrib4fv(variable.m_Layout, values);
        break;
    default:
        // todo: show error info
        break;
    }
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, const GpuInt * values)
{
    glVertexAttribI4iv(variable.m_Layout, values);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, const GpuUInt * values)
{
    glVertexAttribI4uiv(variable.m_Layout, values);
}

void AttributeData::Destory()
{
    glDeleteVertexArrays(1, &m_VAO);
}


} // end of namespace TRL