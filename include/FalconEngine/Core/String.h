#pragma once

#include <FalconEngine/Core/Macro.h>

#include <locale>
#include <string>
#include <vector>

namespace FalconEngine
{

// @remark Require args are c-string rather than std::string.
template<class ... Args>
static std::string
GetStringFormat(const char *format, Args && ... args)
{
    char buffer[256] = { 0 };
    snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
    return std::string(buffer);
}

// @param str must be in utf-8 format.
FALCON_ENGINE_API std::wstring
GetWideString(const std::string& str);

FALCON_ENGINE_API bool
IsFileExtensionSupported(const std::string& extension, const std::vector<std::string>& extensionSupportedList);

}
