#pragma once

#include <FalconEngine/Core/Common.h>

#include <fstream>
#include <locale>
#include <string>
#include <vector>

#define FALCON_ENGINE_DIRECTORY_SEPARATOR "/"

namespace FalconEngine
{

// @param str must be in utf-8 format.
//
// @return
FALCON_ENGINE_API std::wstring
GetWString(const std::string& str);

FALCON_ENGINE_API bool
Exist(const std::string& relativePath);

FALCON_ENGINE_API std::string
GetCurrentPath();

FALCON_ENGINE_API std::string
GetFileExtension(const std::string& path);

FALCON_ENGINE_API std::string
GetFileDirectory(const std::string& path);

FALCON_ENGINE_API std::string
GetFileName(const std::string& path);

FALCON_ENGINE_API std::string
GetFileStem(const std::string& path);

// @return Byte number of the given file.
FALCON_ENGINE_API std::ifstream::pos_type
GetFileSize(const std::string& relativePath);

FALCON_ENGINE_API std::string
ChangeFileExtension(const std::string& path, const std::string& extension);

FALCON_ENGINE_API std::string
RemoveFileExtension(const std::string& path);

FALCON_ENGINE_API bool
IsFileExtensionSupported(const std::string& extension, const std::vector<std::string>& extensionSupportedList);

FALCON_ENGINE_API bool
CreateDirectory(const std::string& relativePath);

}
