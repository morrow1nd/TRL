# Example/Triangle

INCLUDE_DIRECTORIES(${TRL_INCLUDE_PATHS})
add_executable(TRL_Example_TRL_SL_Example
	"Main.cpp"
)

target_link_libraries(TRL_Example_TRL_SL_Example
    ${TRL_LIBRARIES}
)

# IDE specific
set_property(TARGET TRL_Example_TRL_SL_Example PROPERTY FOLDER Example)

# Set up VS working directory
set_target_properties(TRL_Example_TRL_SL_Example PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TRL_SOURCE_DIR}/../Documentation/")