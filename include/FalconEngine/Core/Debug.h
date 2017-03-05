#pragma once

#include <string>

namespace FalconEngine
{

class Debug
{
public:
    static void
    OutputString(char *str);

    static void
    OutputString(const std::string& str);
};

}