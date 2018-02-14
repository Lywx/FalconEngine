#include <FalconEngine/Core/Debug.h>
#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <string>

#include <Windows.h>
namespace FalconEngine
{

#if defined(FALCON_ENGINE_COMPILER_MSVC)
void
Debug::BreakInternal()
{
    // NOTE(Wuxiang): Breakpoints that should ALWAYS trigger (even in release builds)!
    if (IsDebuggerPresent())
    {
        __debugbreak();
    }
}
#endif

/* static */ void
Debug::OutputStringInternal(const std::string& str)
{
    OutputDebugString(str.c_str());
}

/* static */ void
Debug::OutputStringInternal(const char *str)
{
    OutputDebugString(str);
}

}
#endif