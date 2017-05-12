#pragma once

#include <string>

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_CORE Debug
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
