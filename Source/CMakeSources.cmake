
SET(TRL_INC_SL
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/DebugGenerator.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/GLSLGenerator.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/TRLSLGenerator.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/Token.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/TRLSLTokener.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/trlsl_token_id.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLSL/TRLSLParser.h"
)
SET(TRL_SRC_SL
    "${TRL_SOURCE_DIR}/TRL/TRLSL/DebugGenerator.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/GLSLGenerator.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSLParser.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSLGenerator.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/TRLSLTokener.cpp"
    "${TRL_SOURCE_DIR}/TRL/TRLSL/Token.cpp"
)

SET(TRL_INC_FILES
	"${TRL_INCLUDE_DIR}/TRL/AttributeUniformInfo.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLCommonType.h"
    "${TRL_INCLUDE_DIR}/TRL/RenderAPI.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuObjectHandles.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLShader.h"
    "${TRL_INCLUDE_DIR}/TRL/AttributeVariable.h"
    "${TRL_INCLUDE_DIR}/TRL/UniformVariable.h"
)

SET(TRL_SRC_FILES
	"${TRL_SOURCE_DIR}/TRL/RenderAPI.cpp"
	"${TRL_SOURCE_DIR}/TRL/TRLShader.cpp"
)

set(TRL_INC_DETAIL_OPENGL
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLRenderAPI.h"

	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLAttributeData.h"
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLBuffer.h"
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLCommonType.h"
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLProgram.h"
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLShader.h"
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLTexture.h"
	"${TRL_INCLUDE_DIR}/TRL/details/OpenGL/OpenGLTexture2D.h"
)

set(TRL_SRC_OPENGL
	"${TRL_SOURCE_DIR}/TRL/OpenGL/OpenGLRenderAPI.cpp"

	"${TRL_SOURCE_DIR}/ThirdParty/GLAD/glad-c/src/glad.c"
)

set(TRL_INC_DETAIL_DX11
	"${TRL_INCLUDE_DIR}/TRL/details/DX11/DX11RenderAPI.h"
)

set(TRL_SRC_DX11
	"${TRL_SOURCE_DIR}/TRL/DX11/DX11RenderAPI.cpp"
)


source_group("CMake"									FILES "${TRL_SOURCE_DIR}/../CMakeLists.txt")
source_group("CMake\\Source"                            FILES "CMakeSources.cmake" "CMakeLists.txt")
source_group("CMake\\Source\\ThirdParty"				FILES "${TRL_SOURCE_DIR}/ThirdParty/CMakeLists.txt")

source_group("Header Files"                             FILES ${TRL_INC_FILES})
source_group("Source Files"								FILES ${TRL_SRC_FILES})
source_group("Header Files\\TRL_SL"						FILES ${TRL_INC_SL})
source_group("Source Files\\TRL_SL"                     FILES ${TRL_SRC_SL})
source_group("Header Files\\details\\OpenGL"			FILES ${TRL_INC_DETAIL_OPENGL})
source_group("Source Files\\OpenGL"						FILES ${TRL_SRC_OPENGL})
source_group("Header Files\\details\\DX11"				FILES ${TRL_INC_DETAIL_DX11})
source_group("Source Files\\DX11"						FILES ${TRL_SRC_DX11})


set(TRL_SRC
	"${TRL_SOURCE_DIR}/../CMakeLists.txt"
    "CMakeSources.cmake" "CMakeLists.txt"
	"${TRL_SOURCE_DIR}/ThirdParty/CMakeLists.txt"

	${TRL_INC_FILES}
    ${TRL_SRC_FILES}
    ${TRL_INC_SL}
	${TRL_SRC_SL}

	${TRL_INC_DETAIL_OPENGL}
	${TRL_SRC_OPENGL}
	${TRL_INC_DETAIL_DX11}
	${TRL_SRC_DX11}
)