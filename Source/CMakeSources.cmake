SET(TRL_INC_FILES
	"${TRL_INCLUDE_DIR}/TRL/AttributeUniformInfo.h"
    "${TRL_INCLUDE_DIR}/TRL/AttributeVariable.h"
    "${TRL_INCLUDE_DIR}/TRL/DataClasses.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuObjectHandles.h"
    "${TRL_INCLUDE_DIR}/TRL/RenderAPI.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLCommonType.h"
    #"${TRL_INCLUDE_DIR}/TRL/TRLShader.h"
    "${TRL_INCLUDE_DIR}/TRL/UniformVariable.h"
)

SET(TRL_SRC_FILES
	"${TRL_SOURCE_DIR}/TRL/AttributeVariable.cpp"
	"${TRL_SOURCE_DIR}/TRL/DataClasses.cpp"
	"${TRL_SOURCE_DIR}/TRL/RenderAPI.cpp"
	#"${TRL_SOURCE_DIR}/TRL/TRLShader.cpp"
	"${TRL_SOURCE_DIR}/TRL/UniformVariable.cpp"
	"${TRL_SOURCE_DIR}/TRL/GpuObjectHandles.cpp"
)

SET(TRL_INC_SL
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/Token.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/TRLSL_IR.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/TRLSL_IRGenerator.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/trlsl_token_id.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/TRLSLCodeGenerator.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/TRLSLGrammarRuleHandler.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/TRLSLParser.h"
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/TRLSLTokener.h"
)
SET(TRL_SRC_SL
    "${TRL_SOURCE_DIR}/TRL/TRLSL/Token.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSL_IR.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSL_IRGenerator.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSLParser.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSLTokener.cpp"
)
SET(TRL_INC_SL_GLSL
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/GLSL/GLSLCodeGenerator.h"
)
SET(TRL_SRC_SL_GLSL
    "${TRL_SOURCE_DIR}/TRL/TRLSL/GLSL/GLSLCodeGenerator.cpp"
)
SET(TRL_INC_SL_HLSL
    "${TRL_INCLUDE_DIR}/TRL/details/TRLSL/HLSL/HLSLCodeGenerator.h"
)
SET(TRL_SRC_SL_HLSL
    "${TRL_SOURCE_DIR}/TRL/TRLSL/HLSL/HLSLCodeGenerator.cpp"
)

###############################################################################
## RenderAPI Impl

set(TRL_INC_DETAIL_RENDERAPI_IMPL_OPENGL
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLRenderAPI.h"

	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLAttributeData.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLBuffer.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLCommonType.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLProgram.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLShader.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLTexture.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/OpenGL/OpenGLTexture2D.h"
)

set(TRL_SRC_DETAIL_RENDERAPI_IMPL_OPENGL
	"${TRL_SOURCE_DIR}/TRL/RenderAPIImpl/OpenGL/OpenGLRenderAPI.cpp"

	"${TRL_SOURCE_DIR}/ThirdParty/GLAD/glad-c/src/glad.c"
)

set(TRL_INC_DETAIL_RENDERAPI_IMPL_DX11
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11AttributeData.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11Buffer.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11CommonType.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11Program.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11RenderAPI.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11Shader.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11Texture.h"
	"${TRL_INCLUDE_DIR}/TRL/details/RenderAPIImpl/DX11/DX11Texture2D.h"
)

set(TRL_SRC_DETAIL_RENDERAPI_IMPL_DX11
	"${TRL_SOURCE_DIR}/TRL/RenderAPIImpl/DX11/DX11RenderAPI.cpp"
)


source_group("CMake"									FILES "${TRL_SOURCE_DIR}/../CMakeLists.txt")
source_group("CMake\\Source"                            FILES "CMakeSources.cmake" "CMakeLists.txt")
source_group("CMake\\Source\\ThirdParty"				FILES "${TRL_SOURCE_DIR}/ThirdParty/CMakeLists.txt")

source_group("Header Files"												FILES ${TRL_INC_FILES})
source_group("Header Files\\details\\TRL_SL"							FILES ${TRL_INC_SL})
source_group("Header Files\\details\\TRL_SL\\GLSL"						FILES ${TRL_INC_SL_GLSL})
source_group("Header Files\\details\\TRL_SL\\HLSL"						FILES ${TRL_INC_SL_HLSL})
source_group("Header Files\\details\\RenderAPIImpl\\OpenGL"				FILES ${TRL_INC_DETAIL_RENDERAPI_IMPL_OPENGL})
source_group("Header Files\\details\\RenderAPIImpl\\DX11"				FILES ${TRL_INC_DETAIL_RENDERAPI_IMPL_DX11})

source_group("Source Files"												FILES ${TRL_SRC_FILES})
source_group("Source Files\\TRL_SL"										FILES ${TRL_SRC_SL})
source_group("Source Files\\TRL_SL\\GLSL"								FILES ${TRL_SRC_SL_GLSL})
source_group("Source Files\\TRL_SL\\HLSL"								FILES ${TRL_SRC_SL_HLSL})
source_group("Source Files\\RenderAPIImpl\\OpenGL"						FILES ${TRL_SRC_DETAIL_RENDERAPI_IMPL_OPENGL})
source_group("Source Files\\RenderAPIImpl\\DX11"						FILES ${TRL_SRC_DETAIL_RENDERAPI_IMPL_DX11})


set(TRL_SRC
	"${TRL_SOURCE_DIR}/../CMakeLists.txt"
    "CMakeSources.cmake" "CMakeLists.txt"
	"${TRL_SOURCE_DIR}/ThirdParty/CMakeLists.txt"

	${TRL_INC_FILES}
    ${TRL_SRC_FILES}
    ${TRL_INC_SL}
    ${TRL_INC_SL_GLSL}
    ${TRL_INC_SL_HLSL}
	${TRL_SRC_SL}
	${TRL_SRC_SL_GLSL}
	${TRL_SRC_SL_HLSL}

	${TRL_INC_DETAIL_RENDERAPI_IMPL_OPENGL}
	${TRL_SRC_DETAIL_RENDERAPI_IMPL_OPENGL}
	${TRL_INC_DETAIL_RENDERAPI_IMPL_DX11}
	${TRL_SRC_DETAIL_RENDERAPI_IMPL_DX11}
)