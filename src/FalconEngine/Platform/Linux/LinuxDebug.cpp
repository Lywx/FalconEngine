#include <FalconEngine/Core/Debug.h>
#include <FalconEngine/Core/Macro.h>
#if defined(FALCON_ENGINE_OS_LINUX)
#include <csignal>
#include <iostream>
#include <string>
namespace FalconEngine
{

#if defined(FALCON_ENGINE_COMPILER_GCC)
void
Debug::Break()
{
    // Generate an interrupt
    std::raise(SIGINT);
}
#endif

/* static */ void
Debug::OutputString(const std::string& str)
{
    OutputString(str.c_str());
}

/* static */ void
Debug::OutputString(const char *str)
{
    std::cout << str << std::flush;
}

}

#endif
