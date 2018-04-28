# Example/Triangle


INCLUDE_DIRECTORIES(${TRL_INCLUDE_PATHS} ${TOY_UTILITY_INCLUDE_PATHS})
add_executable(TRL_Example_Triangle
	"Triangle.cpp"
)


target_link_libraries(TRL_Example_Triangle ToyUtility TRL)


# IDE specific
set_property(TARGET TRL_Example_Triangle PROPERTY FOLDER Example)