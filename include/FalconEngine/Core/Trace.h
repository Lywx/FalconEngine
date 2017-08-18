#pragma once

#include <FalconEngine/Core/Macro.h>

#include <string>

namespace FalconEngine
{

class FALCON_ENGINE_API Trace
{
public:
    static void
    OutputString(const char *str);

    static void
    OutputString(const std::string& str);

    template<class ... Args>
    static void
    OutputStringFormat(const char *format, Args && ... args)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);

        OutputString(buffer);
    }
};

}
