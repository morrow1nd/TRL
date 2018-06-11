
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
    "${TRL_INCLUDE_DIR}/TRL/CommonType.h"
    "${TRL_INCLUDE_DIR}/TRL/RenderAPI.h"
    "${TRL_INCLUDE_DIR}/TRL/AttributeData.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuBuffer.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuProgram.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuShader.h"
    "${TRL_INCLUDE_DIR}/TRL/TRLShader.h"
    "${TRL_INCLUDE_DIR}/TRL/AttributeVariable.h"
    "${TRL_INCLUDE_DIR}/TRL/UniformVariable.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuTexture.h"
    "${TRL_INCLUDE_DIR}/TRL/GpuTexture2D.h"
)

SET(TRL_SRC_FILES
	"${TRL_SOURCE_DIR}/TRL/TRLShader.cpp"
)

set(TRL_SRC_OPENGL
	"${TRL_SOURCE_DIR}/TRL/OpenGL/AttributeData.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/GpuBuffer.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/GpuProgram.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/GpuShader.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/AttributeVariable.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/UniformVariable.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/RenderAPI.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/GpuTexture.cpp"
	"${TRL_SOURCE_DIR}/TRL/OpenGL/GpuTexture2D.cpp"

	"${TRL_SOURCE_DIR}/ThirdParty/GLAD/glad-c/src/glad.c"
)

set(TRL_SRC_OPENGLES
	
)

set(TRL_SRC_DX11

)


source_group("CMake"									FILES "${TRL_SOURCE_DIR}/../CMakeLists.txt")
source_group("CMake\\Source"                            FILES "CMakeSources.cmake" "CMakeLists.txt")
source_group("CMake\\Source\\ThirdParty"				FILES "${TRL_SOURCE_DIR}/ThirdParty/CMakeLists.txt")

source_group("Header Files"                             FILES ${TRL_INC_FILES})
source_group("Source Files"								FILES ${TRL_SRC_FILES})
source_group("Header Files\\TRL_SL"						FILES ${TRL_INC_SL})
source_group("Source Files\\TRL_SL"                     FILES ${TRL_SRC_SL})

if(TRL_USING_OPENGL)
source_group("Source Files\\OpenGL"						FILES ${TRL_SRC_OPENGL})
endif()
if(TRL_USING_OPENGLES)
source_group("Source Files\\OpenGLES"					FILES ${TRL_SRC_OPENGLES})
endif()
if(TRL_USING_DX11)
source_group("Source Files\\DX11"						FILES ${TRL_SRC_DX11})
endif()


set(TRL_SRC
	"${TRL_SOURCE_DIR}/../CMakeLists.txt"
    "CMakeSources.cmake" "CMakeLists.txt"
	"${TRL_SOURCE_DIR}/ThirdParty/CMakeLists.txt"
	${TRL_INC_FILES}
    ${TRL_SRC_FILES}
    ${TRL_INC_SL}
	${TRL_SRC_SL}
)

if(TRL_USING_OPENGL)
	set(TRL_SRC
		${TRL_SRC}
		${TRL_SRC_OPENGL}
	)
endif()
if(TRL_USING_OPENGLES)
	set(TRL_SRC
		${TRL_SRC}
		${TRL_SRC_OPENGLES}
	)
endif()
if(TRL_USING_DX11)
	set(TRL_SRC
		${TRL_SRC}
		${TRL_SRC_DX11}
	)
endif()