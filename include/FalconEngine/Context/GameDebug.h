#pragma once

#include <FalconEngine/ContextInclude.h>
#include <string>

namespace FalconEngine
{

class GameDebug
{
public:
    static void Initialize();

    static void OutputString(char *str);
    static void OutputString(std::string str);
};

}
