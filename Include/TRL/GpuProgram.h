#pragma once

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/String/String.h"
#include "TRL/CommonType.h"


namespace TRL
{


class GpuShader;


class GpuProgram
{
public:
    bool Init(GpuShader& vertShader, GpuShader& fragShader);
    void Destory();

    friend class RenderAPI;

private:
    bool m_LinkedSucc;
    GpuProgramInner m_ProgramInner;
    ToyUtility::String m_LinkLog;
};


} // end of namespace TRL