#include "ToyUtility/Prerequisites/PreDefine.h"
#include <iostream>

#include "ToyUtility/DataStream/MemoryDataStream.h"
#include "TRL/details/TRLSL/DebugGenerator.h"
#include "TRL/details/TRLSL/GLSLGenerator.h"
#include "TRL/details/TRLSL/TRLSLParser.h"
#include "TRL/details/TRLSL/TRLSLTokener.h"


using namespace ToyUtility;
using namespace TRL;


int main()
{
    const ToyUtility::String code = R"(

uniform vec4 Pos;

void main()
{
    Pos = vec4(1, 2, 3, 4);
    if(1 == Pos.x)
    {
        Pos.y = 4;
    }
}

)";


    TRL::TRLSLTokener tokener;
    bool res = tokener.Prepare(MemoryDataStream((void*)code.c_str(), code.size() + 1, false));
    if (!res)
    {
        std::cout << "tokener: " << tokener.GetError().ErrorInfo << std::endl;
        return 2;
    }

    {
        MemoryDataStream stream(1024);

        //DebugGenerator generator;
        GLSLGenerator generator;

        TRLSLParser parser(generator);
        parser.Parse(tokener);
        generator.GenerateCode(stream);
        std::cout << stream.GetAsString() << std::endl;
    }

    std::cout << "TRL SL Example >> End" << std::endl;
    system("pause");
    return 0;
}