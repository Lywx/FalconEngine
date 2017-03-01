#pragma once

#include <FalconEngine/ContentInclude.h>

#include <codecvt>
#include <fstream>
#include <locale>
#include <string>

#if FALCON_ENGINE_OS_WINDOWS
#define DIR_SEPARATOR "\\"
#elif FALCON_ENGINE_OS_LINUX
#define DIR_SEPARATOR "/"
#endif

namespace FalconEngine
{

// @param str must be in utf-8 format.
//
// @return
std::wstring
GetWString(std::string str);

bool
Exist(const std::string relativePath);

std::string
GetCurrentPath();

std::string
GetFileExtension(const std::string path);

std::string
GetFileDirectory(const std::string path);

std::string
GetFileName(const std::string path);

std::string
GetFileStem(const std::string path);

// @return Byte number of the given file.
std::ifstream::pos_type
GetFileSize(const std::string relativePath);

std::string
ChangeFileExtension(const std::string path, const std::string extension);

std::string
RemoveFileExtension(const std::string path);

bool
CreateDirectory(const std::string relativePath);

}
