# Example

option(OPTION_TRL_Build_Texture_Example "Build TRL Texture example" ON)
if(OPTION_TRL_Build_Texture_Example)
	ADD_SUBDIRECTORY(Texture)
endif()

ADD_SUBDIRECTORY(TRLSL_Example)
