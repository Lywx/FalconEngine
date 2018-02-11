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
Debug::InternalBreak()
{
    // Generate an interrupt
    std::raise(SIGINT);
}
#endif

/* static */ void
Debug::InternalOutputString(const std::string& str)
{
    InternalOutputString(str.c_str());
}

/* static */ void
Debug::InternalOutputString(const char *str)
{
    std::cout << str << std::flush;
}

}

#endif
