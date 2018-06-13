#include "TRL/RenderAPI.h"

#include "TRL/details/OpenGL/OpenGLRenderAPI.h"
#include "TRL/details/DX11/DX11RenderAPI.h"


namespace TRL
{


RenderAPI * RenderAPI::CreateRenderAPI(TRLNativeApiType type)
{
    switch (type)
    {
    case TRLNativeApiType::DX11:
        
        break;
    case TRLNativeApiType::OpenGL:
        return new TRL::details::OpenGLRenderAPI();
        break;
    case TRLNativeApiType::OpenGLES:

        break;
    }

    return nullptr;
}


} // end of namespace TRL