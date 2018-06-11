#include "TRL/AttributeData.h"
#include "TRL/GpuBuffer.h"
#include "TRL/AttributeVariable.h"


namespace TRL
{


int AttributeData::GetMaxAttributeNumber()
{
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    return maxVertexAttribs;
}

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
    GpuVariableComponentSize size, GpuDataType typeOfComponent, NormalizeAction normalizeAction, int stride, int beginOffset)
{
    vbo.Bind();
    glEnableVertexAttribArray(variable.GetLocation());
    glVertexAttribPointer(variable.GetLocation(),
        (GLint)size,
        typeOfComponent,
        normalizeAction == NormalizeAction::NeedNormalize ? GL_TRUE : GL_FALSE,
        stride,
        (const void*)beginOffset);
}

void AttributeData::EnableAttributeArray(const AttributeVariable& variable, bool enable)
{
    if (enable)
        glEnableVertexAttribArray(variable.GetLocation());
    else
        glDisableVertexAttribArray(variable.GetLocation());
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x)
{
    glVertexAttrib1f(variable.GetLocation(), x);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y)
{
    glVertexAttrib2f(variable.GetLocation(), x, y);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z)
{
    glVertexAttrib3f(variable.GetLocation(), x, y, z);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuFloat x, GpuFloat y, GpuFloat z, GpuFloat w)
{
    glVertexAttrib4f(variable.GetLocation(), x, y, z, w);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuInt x, GpuInt y, GpuInt z, GpuInt w)
{
    glVertexAttribI4i(variable.GetLocation(), x, y, z, w);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, GpuUInt x, GpuUInt y, GpuUInt z, GpuUInt w)
{
    glVertexAttribI4ui(variable.GetLocation(), x, y, z, w);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, int size, const GpuFloat * values)
{
    switch (size)
    {
    case 1:
        glVertexAttrib1fv(variable.GetLocation(), values);
        break;
    case 2:
        glVertexAttrib2fv(variable.GetLocation(), values);
        break;
    case 3:
        glVertexAttrib3fv(variable.GetLocation(), values);
        break;
    case 4:
        glVertexAttrib4fv(variable.GetLocation(), values);
        break;
    default:
        // todo: show error info
        break;
    }
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, const GpuInt * values)
{
    glVertexAttribI4iv(variable.GetLocation(), values);
}

void AttributeData::SetConstantAttribute(const AttributeVariable& variable, const GpuUInt * values)
{
    glVertexAttribI4uiv(variable.GetLocation(), values);
}

void AttributeData::Destory()
{
    glDeleteVertexArrays(1, &m_VAO);
}


} // end of namespace TRL