#include <FalconEngine/Core/Debug.h>
#include <FalconEngine/CoreInclude.h>

#if FALCON_ENGINE_OS_WINDOWS

#include <windows.h>
#include <string>

namespace FalconEngine
{

/* static */ void
Debug::OutputString(const std::string& str)
{
    OutputDebugString(str.c_str());
}

/* static */ void
Debug::OutputString(char *str)
{
    OutputDebugString(str);
}

}

#endif