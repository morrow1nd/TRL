#include <iostream>

#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/DataStream/MemoryDataStream.h"
#include "ToyUtility/DataStream/FileDataStream.h"
#include "TRL/details/TRLSL/DebugGenerator.h"
#include "TRL/details/TRLSL/GLSLGenerator.h"
#include "TRL/details/TRLSL/HLSLGenerator.h"
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
    //bool res = tokener.Prepare(MemoryDataStream((void*)code.c_str(), code.size() + 1, false));
    bool res = tokener.Prepare(FileDataStream("simple.trlsl"));
    //bool res = tokener.Prepare(FileDataStream("trlsl_full_example.trlsl"));
    if (!res)
    {
        std::cout << "tokener error: " << tokener.GetError().ErrorInfo << std::endl;
        return 2;
    }

    {
        MemoryDataStream stream(10240);

        if (0)
        {
            GLSLGenerator generator;
            //HLSLGenerator generator;

            TRLSLParser parser(generator);
            parser.Parse(tokener);
            generator.GenerateCode(stream);
            std::cout << stream.GetAsString() << std::endl;
        }
        else
        {
            DebugGenerator generator;

            TRLSLParser parser(generator);
            parser.Parse(tokener);
        }
    }

    std::cout << "TRL SL Example >> End" << std::endl;

    system("pause");
    return 0;
}