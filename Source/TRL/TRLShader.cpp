#include "TRL/TRLShader.h"

#include <cassert>
#include "ToyUtility/Log/Logger.h"
#include "TRL/TRLSL/TRLSLTokener.h"
#include "TRL/TRLSL/TRLSLParser.h"
#include "TRL/TRLSL/TRLSLGenerator.h"
#include "TRL/TRLSL/GLSLGenerator.h"
#include "TRL/GpuShader.h"


namespace TRL
{


bool TRLShader::Init(const String& code, GpuShaderType shaderType)
{
    m_ShaderType = shaderType;
    return m_Tokener.Prepare(code);
}

const TRLSLTokenerError & TRLShader::GetTokenerError() const
{
    return m_Tokener.GetError();
}

SPtr<GpuShader> TRLShader::GenerateGpuShader(ToyRenderType targetType)
{
    switch (targetType)
    {
    case ToyRenderType::ToyRenderDX11:
    {
        assert(false);
        break;
    }
    case ToyRenderType::ToyRenderOpenGL:
    {
        GLSLGenerator generator;
        TRLSLParser parser(generator);
        bool result = parser.Parse(m_Tokener);
        if (result == false)
        {
            // TODOH
            TOY_RAW_LOG_ERR << "TRLShader::GenerateGpuShader: TRLSLParser.Parse fail" << std::endl;
            return SPtr<GpuShader>();
        }
        String glslCode = generator.GenerateCode();
        SPtr<GpuShader> shader = SPtr<GpuShader>(new GpuShader());
        shader->Init(glslCode, m_ShaderType);
        if (shader->IsCompiledSucc() == false)
        {
            TOY_RAW_LOG_ERR << "TRLShader::GenerateGpuShader: compile gpu shader error: " << shader->GetCompileLogInfo() << std::endl;
            // TODOH
            return SPtr<GpuShader>();
        }
        return shader;
    }
    case ToyRenderType::ToyRenderOpenGLES:
    {
        assert(false);
        break;
    }
    default:
        // TODOL
        break;
    }
}


} // end of namespace TRL