#pragma once

#include <fstream>
#include <string>

#include <FalconEngine/ContentInclude.h>

namespace FalconEngine {

bool                    Exists(const std::wstring relativePath);

std::wstring            GetCurrentPath();
std::wstring            GetFileName(const std::wstring relateivePath);
std::ifstream::pos_type GetFileSize(const std::wstring relativePath);

bool                    CreateDirectory(const std::wstring relativePath);

}
