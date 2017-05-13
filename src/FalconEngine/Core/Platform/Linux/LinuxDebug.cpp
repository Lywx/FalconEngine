#include <FalconEngine/Core/Debug.h>

#if defined(FALCON_ENGINE_OS_LINUX)

#include <iostream>
#include <string>

namespace FalconEngine
{

void
Debug::Break()
{
#if defined(FALCON_ENGINE_COMPILER_GCC)
#endif
}

/* static */ void
Debug::OutputString(const std::string& str)
{
    OutputString(str.c_str());
}

/* static */ void
Debug::OutputString(const char *str)
{
    std::cout << str << std::endl;
}

}

#endif
