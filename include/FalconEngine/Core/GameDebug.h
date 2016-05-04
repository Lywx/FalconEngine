#pragma once

#include <string>

namespace FalconEngine {

class GameDebug
{
public:
    static void OutputString(char *str);
    static void OutputString(std::string str);
};

}
