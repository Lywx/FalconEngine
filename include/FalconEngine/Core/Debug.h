#pragma once

#include <string>

namespace FalconEngine
{

class Debug
{
public:
    static void
    InternalBreak();

    static void
    InternalOutputString(const char *str);

    static void
    InternalOutputString(const std::string& str);

    template<class ... Args>
    static void
    InternalOutputStringFormat(const char *format, Args && ... args)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
        InternalOutputString(buffer);
    }
};

}
