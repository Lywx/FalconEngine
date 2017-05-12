#pragma once

#include <FalconEngine/Core/Header.h>

#include <codecvt>
#include <fstream>
#include <locale>
#include <string>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#define FALCON_ENGINE_DIR_SEPARATOR "/"
#elif defined(FALCON_ENGINE_OS_LINUX)
#define FALCON_ENGINE_DIR_SEPARATOR "/"
#endif

namespace FalconEngine
{

// @param str must be in utf-8 format.
//
// @return
FALCON_ENGINE_ITEM_CORE std::wstring
GetWString(const std::string& str);

FALCON_ENGINE_ITEM_CORE bool
Exist(const std::string& relativePath);

FALCON_ENGINE_ITEM_CORE std::string
GetCurrentPath();

FALCON_ENGINE_ITEM_CORE std::string
GetFileExtension(const std::string& path);

FALCON_ENGINE_ITEM_CORE std::string
GetFileDirectory(const std::string& path);

FALCON_ENGINE_ITEM_CORE std::string
GetFileName(const std::string& path);

FALCON_ENGINE_ITEM_CORE std::string
GetFileStem(const std::string& path);

// @return Byte number of the given file.
FALCON_ENGINE_ITEM_CORE std::ifstream::pos_type
GetFileSize(const std::string& relativePath);

FALCON_ENGINE_ITEM_CORE std::string
ChangeFileExtension(const std::string& path, const std::string& extension);

FALCON_ENGINE_ITEM_CORE std::string
RemoveFileExtension(const std::string& path);

FALCON_ENGINE_ITEM_CORE bool
CreateDirectory(const std::string& relativePath);

}
