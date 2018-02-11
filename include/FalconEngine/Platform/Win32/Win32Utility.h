#pragma once

#include <FalconEngine/Core/Macro.h>

#include <string>

#if defined(FALCON_ENGINE_OS_WINDOWS)

namespace FalconEngine
{

// @return Generated temp file path.
std::string
CreateTempFile(const wchar_t *tempFilePrefix, int tempFileSequence);

unsigned long
GetLastErrorCode();

std::string
GetLastErrorString();

// @return Chosen file path.
std::wstring
OpenFileDialog(const std::wstring& titleString, const wchar_t *filterString);

void
OpenMessageBox(const std::string& titleString, const std::string& contentString);

void
OpenMessageBox(const std::wstring& titleString, const std::wstring& contentString);

void
DisplayProcessOutput(const std::pair<unsigned int, std::string>& output);

// @ref https://msdn.microsoft.com/en-us/library/ms682499(VS.85).aspx
// @return Standard output string from the child process. First is the exit code,
// second is the output string.
std::pair<unsigned int, std::string>
StartProcess(const std::wstring& processCmdWideString);

std::pair<unsigned int, std::string>
StartProcess(const std::string& processCmdString);

}

#endif
