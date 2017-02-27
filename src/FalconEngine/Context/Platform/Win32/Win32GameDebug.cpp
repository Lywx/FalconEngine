#include <FalconEngine/Context/GameDebug.h>

#include <windows.h>
#include <string>

namespace FalconEngine {

/* static */ void GameDebug::OutputString(std::string str)
{
    OutputDebugString(str.c_str());
}

/* static */ void GameDebug::OutputString(char *str)
{
    OutputDebugString(str);
}

}