#include "TRL/RenderAPI.h"
#include "TRL/GpuProgram.h"
#include "TRL/AttributeData.h"


namespace TRL
{


void RenderAPI::ActiveGpuProgram(const GpuProgram& program)
{
    m_ActiveGpuProgram = program.m_ProgramInner;
    glUseProgram(m_ActiveGpuProgram);
}

bool RenderAPI::IsActiveGpuProgram(const GpuProgram & program)
{
    return program.m_ProgramInner == m_ActiveGpuProgram;
}

void RenderAPI::DrawIndices(GpuPrimitiveType mode, const AttributeData& attributeData, int offset)
{
    glDrawElements(mode, attributeData.GetIndicesNumber(), attributeData.GetIndicesDataType(),
        (const void*)offset);
}

void RenderAPI::ConvertProjectionMatrix(const ToyUtility::Matrix4 & matrix, ToyUtility::Matrix4 & dest)
{
    dest = matrix;
}


} // end of namespace TRL