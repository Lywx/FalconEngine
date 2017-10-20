#pragma once

#include <FalconEngine/Context/Common.h>

#include <string>

#include <FalconEngine/Core/Debug.h>

namespace FalconEngine
{

// @summary Debug utility used for both the engine and the game.
class FALCON_ENGINE_API GameDebug
{
public:
    static void
    Initialize();

    static void
    Break()
    {
        Debug::Break();
    }

    static void
    OutputString(const char *str)
    {
        Debug::OutputString(str);
    }

    static void
    OutputString(const std::string& str)
    {
        Debug::OutputString(str);
    }

    template<class ... Args>
    static void
    OutputStringFormat(const char *format, Args&& ... args)
    {
        Debug::OutputStringFormat(format, std::forward<Args>(args)...);
    }
};

}
