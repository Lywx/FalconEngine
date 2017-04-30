#pragma once

#include <string>

namespace FalconEngine
{

class Debug
{
public:
    static void
    Break();

    static void
    OutputString(const char *str);

    static void
    OutputString(const std::string& str);
};

}
