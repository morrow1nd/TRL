# Example/Triangle


## load ToyXWindow project
ADD_SUBDIRECTORY(${OPTION_TOY_XWINDOW_PATH} ToyXWindow.out)


INCLUDE_DIRECTORIES(
    ${TRL_INCLUDE_PATHS}
    ${TOY_XWINDOW_INCLUDE_PATHS}
)
add_executable(TRL_Example_Triangle
	"Main.cpp"
)


target_link_libraries(TRL_Example_Triangle
    ${TRL_LIBRARIES}
    ${TOY_XWINDOW_LIBRARIES}
)


# IDE specific
set_property(TARGET TRL_Example_Triangle PROPERTY FOLDER Example)