# Source/ThirdParty/sqlite-lemon


add_executable(SqliteLemon
	"lemon/lemon.c"
)


# IDE specific
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
SET_PROPERTY(TARGET SqliteLemon PROPERTY FOLDER ThirdParty)
