#pragma once

#include <string>

namespace FalconEngine
{

class Debug
{
public:
    static void
    BreakInternal();

    static void
    OutputStringInternal(const char *str);

    static void
    OutputStringInternal(const std::string& str);

    template<class ... Args>
    static void
    OutputStringFormatInternal(const char *format, Args && ... args)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
        OutputStringInternal(buffer);
    }
};

}
