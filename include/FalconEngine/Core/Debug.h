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

    template<class ... Args>
    static void
    OutputStringFormat(const char *format, Args && ... args)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
        OutputString(buffer);
    }

    template<class ... Args>
    static std::string
    GetStringFormat(const char *format, Args && ... args)
    {
        char buffer[256] = { 0 };
        snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
        return std::string(buffer);
    }
};

}
