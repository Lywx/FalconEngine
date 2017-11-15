#include <FalconEngine/Core/Debug.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <string>

#include <windows.h>

namespace FalconEngine
{

#if defined(FALCON_ENGINE_COMPILER_MSVC)
void
Debug::Break()
{
    // NOTE(Wuxiang): Breakpoints that should ALWAYS trigger (even in release builds)!
    if (IsDebuggerPresent())
    {
        __debugbreak();
    }
}
#endif

/* static */ void
Debug::OutputString(const std::string& str)
{
    OutputDebugString(str.c_str());
}

/* static */ void
Debug::OutputString(const char *str)
{
    OutputDebugString(str);
}

}

#endif
