#include <FalconEngine/Core/Trace.h>

#include <string>
#include <iostream>

namespace FalconEngine
{

/* static */ void
Trace::OutputString(const std::string& str)
{
    OutputString(str.c_str());
}

/* static */ void
Trace::OutputString(const char *str)
{
    std::cout << str << std::flush;
}

}
