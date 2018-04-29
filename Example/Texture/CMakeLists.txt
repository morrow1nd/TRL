# Example/Texture


INCLUDE_DIRECTORIES(${TRL_INCLUDE_PATHS})
add_executable(TRL_Example_Texture
	"Main.cpp"
)


target_link_libraries(TRL_Example_Texture
    ${TRL_LIBRARIES}
)


# IDE specific
set_property(TARGET TRL_Example_Texture PROPERTY FOLDER Example)

# Set up VS working directory
set_target_properties(TRL_Example_Texture PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TRL_SOURCE_DIR}/../Example/Texture/")