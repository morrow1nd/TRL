#include "TRL/RenderAPI.h"

#include "TRL/details/OpenGL/OpenGLRenderAPI.h"
#include "TRL/details/DX11/DX11RenderAPI.h"


namespace TRL
{


ToyUtility::SPtr<RenderAPI> RenderAPI::CreateDefaultRenderAPI()
{
    return ToyUtility::SPtr<RenderAPI>(new TRL::details::OpenGLRenderAPI());
}

ToyUtility::SPtr<RenderAPI> RenderAPI::CreateRenderAPI(TRLNativeApiType type)
{
    switch (type)
    {
    case TRLNativeApiType::DX11:
        
        break;
    case TRLNativeApiType::OpenGL:
        return ToyUtility::SPtr<RenderAPI>(new TRL::details::OpenGLRenderAPI());
        break;
    case TRLNativeApiType::OpenGLES:

        break;
    }

    return ToyUtility::SPtr<RenderAPI>();
}


} // end of namespace TRL