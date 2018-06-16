#pragma once

#include "glad/glad.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "TRL/details/RenderAPIImpl/OpenGL/OpenGLCommonType.h"


namespace TRL
{

namespace details
{


class OpenGLAttributeData
{
public:
    OpenGLAttributeData()
        :
        m_VAO(0)
    { }


    void Init()
    {
        glGenVertexArrays(1, &m_VAO);
    }

    void Destory()
    {
        glDeleteVertexArrays(1, &m_VAO);
    }

    GLuint GetInnerName() const
    {
        return m_VAO;
    }


public:
    struct EBOInfo
    {
        EBOInfo()
            :
            IndicesNumber(0),
            DataType(GPU_DATA_TYPE_INIT)
        {
        }

        int IndicesNumber;
        GpuDataType DataType;
    };


    EBOInfo& GetEBOInfo() { return m_EBOInfo; }


private:
    GLuint m_VAO;
    EBOInfo m_EBOInfo;
};


} // end of namespace details

} // end of namespace TRL