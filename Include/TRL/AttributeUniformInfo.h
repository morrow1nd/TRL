#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "TRL/TRLCommonType.h"
#include "TRL/UniformVariable.h"
#include "TRL/AttributeVariable.h"


namespace TRL
{


class AttributeUniformInfo
{
public:
    const ToyUtility::List<UniformVariable>& GetUniforms() const { return m_Uniforms; }
    const ToyUtility::List<AttributeVariable>& GetAttributes() const { return m_Attributes; }

    void PushUniform(UniformVariable&& uniform) { m_Uniforms.push_back(std::move(uniform)); }
    void PushAttribute(AttributeVariable&& attribute) { m_Attributes.push_back(std::move(attribute)); }


private:
    ToyUtility::List<UniformVariable> m_Uniforms;
    ToyUtility::List<AttributeVariable> m_Attributes;
};


} // end of namespace TRL