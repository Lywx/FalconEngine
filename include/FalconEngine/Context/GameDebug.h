#pragma once

#include <FalconEngine/Context/ContextInclude.h>
#include <string>

namespace FalconEngine
{

class GameDebug
{
public:
    static void OutputString(char *str);
    static void OutputString(std::string str);

    static void InitializeContext();
};

}
