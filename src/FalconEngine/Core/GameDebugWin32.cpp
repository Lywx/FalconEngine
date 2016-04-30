#include <FalconEngine/Core/GameDebug.h>

#include <windows.h>
#include <string>

namespace FalconEngine {
namespace Core {

/* static */ void GameDebug::OutputString(std::string str)
{
    OutputDebugString(str.c_str());
}

/* static */ void GameDebug::OutputString(char *str)
{
    OutputDebugString(str);
}

}
}