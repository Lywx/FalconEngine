#pragma once

#include <fstream>
#include <locale>
#include <string>
#include <vector>

#include <FalconEngine/Core/Macro.h>

#define FALCON_ENGINE_DIRECTORY_SEPARATOR "/"

namespace FalconEngine
{

FALCON_ENGINE_API std::string
GetCurrentPath();

/************************************************************************/
/* File Members                                                         */
/************************************************************************/
FALCON_ENGINE_API std::string
GetFileDirectory(const std::string& path);

FALCON_ENGINE_API bool
GetFileExist(const std::string& relativePath);

FALCON_ENGINE_API std::string
GetFileName(const std::string& path);

FALCON_ENGINE_API std::string
GetFileStem(const std::string& path);

// @return Byte number of the given file.
FALCON_ENGINE_API std::ifstream::pos_type
GetFileSize(const std::string& relativePath);

/************************************************************************/
/* File Extension Members                                               */
/************************************************************************/
FALCON_ENGINE_API std::string
GetFileExtension(const std::string& path);

FALCON_ENGINE_API std::string
ChangeFileExtension(const std::string& path, const std::string& extension);

FALCON_ENGINE_API std::string
RemoveFileExtension(const std::string& path);

/************************************************************************/
/* File Directory Members                                               */
/************************************************************************/
FALCON_ENGINE_API bool
CreateDirectory(const std::string& relativePath);

}
