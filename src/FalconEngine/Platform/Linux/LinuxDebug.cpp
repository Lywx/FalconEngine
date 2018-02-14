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
Debug::BreakInternal()
{
    // Generate an interrupt
    std::raise(SIGINT);
}
#endif

/* static */ void
Debug::OutputStringInternal(const std::string& str)
{
    OutputStringInternal(str.c_str());
}

/* static */ void
Debug::OutputStringInternal(const char *str)
{
    std::cout << str << std::flush;
}

}

#endif
