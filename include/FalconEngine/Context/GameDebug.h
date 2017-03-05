#pragma once

#include <string>

#include <FalconEngine/Core/Debug.h>

namespace FalconEngine
{

class GameDebug
{
public:
    static void Initialize();

    static void
    OutputString(char *str)
    {
        Debug::OutputString(str);
    }

    static void
    OutputString(const std::string& str)
    {
        Debug::OutputString(str);
    }
};

}
