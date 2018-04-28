# Source/ThirdParty

## GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
ADD_SUBDIRECTORY(GLFW/glfw-3.2.1)
SET(TRL_THIRD_PARTY_INCLUDE_GLFW
    "${TRL_SOURCE_DIR}/ThirdParty/GLFW/glfw-3.2.1/include"
    CACHE INTERNAL "TRL ThirdParty glfw Include Paths"
)


## OpenGL Needed Libs

#Clean this variable first
SET(TRL_DEPS_INCLUDE
    CACHE INTERNAL "TRL ThirdParty Libs Include Paths"
)
if(TRL_USING_OPENGL OR TRL_USING_OPENGLES)
    # GLAD
    SET(TRL_THIRD_PARTY_INCLUDE_GLAD
        "${TRL_SOURCE_DIR}/ThirdParty/GLAD/glad-c/include"
        CACHE INTERNAL "TRL ThirdParty glad Include Paths"
    )

    # RenderAPI Dependence libs include path
    SET(TRL_DEPS_INCLUDE
        ${TRL_THIRD_PARTY_INCLUDE_GLAD}
        CACHE INTERNAL "TRL ThirdParty Libs Include Paths"
    )
endif()
