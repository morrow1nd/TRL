# Source/ThirdParty


## OpenGL Needed Libs

#Clean this variable first
SET(TRL_DEPS_INCLUDE
    CACHE INTERNAL "TRL ThirdParty Libs Include Paths"
)
# TODOH
#if(TRL_USING_OPENGL OR TRL_USING_OPENGLES)
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
#endif()


## sqlite-lemon
ADD_SUBDIRECTORY(sqlite-lemon)
