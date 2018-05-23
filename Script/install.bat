lemon -l -Tlempar.c trlsl_parser.y
move /Y trlsl_parser.c ..\..\Source\TRL\TRLSL\trlsl_parser.cpp
move /Y trlsl_parser.h ..\..\Include\TRL\TRLSL\trlsl_token_id.h
lemon -Tlempar.c trlsl_parser.y
move /Y trlsl_parser.c ..\..\Source\TRL\TRLSL\trlsl_parser_with_#line.cpp

copy /Y trlsl_parser.y ..\..\Documentation\trlsl_parser.y
move /Y trlsl_parser.out ..\..\Source\TRL\TRLSL\trlsl_parser.out
del trlsl_parser.h