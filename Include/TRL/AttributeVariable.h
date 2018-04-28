#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"


namespace TRL
{


class AttributeVariable
{
public:
    // tem code
    AttributeVariable(int layout)
        :
        m_Layout(layout)
    { }



    friend class AttributeData;

private:
    int m_Layout;
};


} // end of namespace TRL