#include <FalconEngine/Platform/Win32/Win32Utility.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <algorithm>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Platform/Win32/Win32Lib.h>

using namespace std;

namespace FalconEngine
{

std::string
CreateTempFile(const wchar_t *tempFilePrefix, int tempFileSequence)
{
    WCHAR tempDirPathWide[MAX_PATH] = { 0 };
    if (!GetTempPathW(MAX_PATH, tempDirPathWide))
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API GetTempPath. ") + GetLastErrorString());

    }

    WCHAR tempFilePathWide[MAX_PATH] = { 0 };
    if (!GetTempFileNameW(tempDirPathWide, tempFilePrefix, tempFileSequence, tempFilePathWide))
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API GetTempFileName. ") + GetLastErrorString());
    }

    wstring exportFilePathStringWide = wstring(tempFilePathWide);
    return string(exportFilePathStringWide.begin(), exportFilePathStringWide.end());
}

unsigned long
GetLastErrorCode()
{
    return GetLastError();
}

std::string
GetLastErrorString()
{
    // Get the error message, if any.
    DWORD errorCode = GetLastError();
    if (errorCode == 0)
    {
        // No error message has been recorded
        return std::string();
    }

    LPSTR messageBuffer = nullptr;
    size_t messageSize = FormatMessage(
                             FORMAT_MESSAGE_ALLOCATE_BUFFER
                             | FORMAT_MESSAGE_FROM_SYSTEM
                             | FORMAT_MESSAGE_IGNORE_INSERTS,
                             nullptr,
                             errorCode,
                             MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                             messageBuffer,
                             0,
                             nullptr);

    std::string message(messageBuffer, messageSize);

    // Free the buffer.
    LocalFree(messageBuffer);

    return message;
}

std::wstring
OpenFileDialog(const std::wstring& titleString, const wchar_t *filterString)
{
    wchar_t filename[MAX_PATH];
    ZeroMemory(&filename, sizeof(filename));

    OPENFILENAMEW filenameInfo;
    ZeroMemory(&filenameInfo, sizeof(filenameInfo));

    filenameInfo.lStructSize = sizeof(filenameInfo);
    filenameInfo.hwndOwner = NULL;
    filenameInfo.lpstrFilter = filterString;
    filenameInfo.lpstrFile = filename;
    filenameInfo.nMaxFile = MAX_PATH;
    filenameInfo.lpstrTitle = &titleString[0];
    filenameInfo.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&filenameInfo))
    {
        return wstring(filename);
    }
    else
    {
        return wstring();
    }
}

void
OpenMessageBox(const std::string& titleString, const std::string& contentString)
{
    MessageBoxA(NULL, &contentString[0], &titleString[0], MB_OK);
}

void
OpenMessageBox(const std::wstring& titleString, const std::wstring& contentString)
{
    MessageBoxW(NULL, &contentString[0], &titleString[0], MB_OK);
}

void
DisplayProcessOutput(const std::pair<unsigned, std::string>& output)
{
    const int outputLineNumPerMessage = 50;

    const string& outputString = output.second;
    size_t outputOffset = 0;
    size_t outputSizeLeft = outputString.size();
    while (outputSizeLeft > 0)
    {
        // NOTE(Wuxiang): Include only limited number of line into current
        // message box, because message box area is very limited.
        size_t outputNewLineOffset = outputOffset;
        int outputLineNum = 1;
        size_t outputNewLineIndex =
            outputString.find('\n', outputNewLineOffset);

        // When the new line's offset is not updated. This means no new
        // line is found.
        if (outputNewLineIndex == string::npos)
        {
            outputNewLineOffset = outputString.size() - 1;
        }
        else
        {
            while (outputNewLineIndex != string::npos
                    && outputLineNum < outputLineNumPerMessage)
            {
                outputNewLineOffset = outputNewLineIndex + 1;
                outputNewLineIndex = outputString.find('\n', outputNewLineOffset);

                ++outputLineNum;
            }
        }

        size_t outputSizeForMessage = std::min(outputSizeLeft, outputNewLineOffset);
        OpenMessageBox("Info", outputString.substr(outputOffset, outputSizeForMessage));
        outputOffset += outputSizeForMessage;
        outputSizeLeft -= outputSizeForMessage;
    }
}

std::string
ReadProcessOutPipe(HANDLE processStdOutReadHandle)
{
    const int BufferSize = 4096;

    string processStdOutputString;
    CHAR processStdOutReadBuffer[BufferSize] = { 0 };

    while(true)
    {
        DWORD readedByte;
        DWORD availableByte;

        PeekNamedPipe(processStdOutReadHandle,
                      NULL,
                      NULL,
                      NULL,
                      &availableByte,
                      NULL);

        if (availableByte > 0)
        {

            BOOL success = ReadFile(processStdOutReadHandle,
                                    processStdOutReadBuffer,
                                    BufferSize,
                                    &readedByte,
                                    NULL);

            if (!success || readedByte == 0)
            {
                break;
            }

            processStdOutputString += string(processStdOutReadBuffer);
        }
        else
        {
            break;
        }
    }

    return processStdOutputString;
}

unsigned int
StartProcessInternal(wchar_t *processCmdWide,
                     HANDLE   processStdOutWriteHandle)
{
    // Set up members of the PROCESS_INFORMATION structure.
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));

    // Set up members of the STARTUPINFO structure.
    // This structure specifies the STDIN and STDOUT handles for redirection.
    STARTUPINFOW startInfo;
    ZeroMemory(&startInfo, sizeof(STARTUPINFO));
    startInfo.cb = sizeof(STARTUPINFO);
    startInfo.hStdError = processStdOutWriteHandle;
    startInfo.hStdOutput = processStdOutWriteHandle;
    startInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Create the child process.

    // If an error occurs, exit the application.
    if (CreateProcessW(NULL,
                       processCmdWide,   // process command line
                       NULL,             // process security attributes
                       NULL,             // primary thread security attributes
                       TRUE,             // handles are inherited
                       CREATE_NO_WINDOW, // creation flags
                       NULL,             // use parent's environment
                       NULL,             // use parent's current directory
                       &startInfo,       // STARTUPINFO pointer
                       &processInfo))    // receives PROCESS_INFORMATION)
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);

        DWORD processExitCode;
        GetExitCodeProcess(processInfo.hProcess, &processExitCode);

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        return processExitCode;
    }
    else
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API CreateProcess. ") + GetLastErrorString());
    }
}

std::pair<unsigned, std::string>
StartProcess(const std::wstring& processCmdWideString)
{
    // Create pipe to redirect process std output.
    HANDLE processStdOutReadHandle = NULL;
    HANDLE processStdOutWriteHandle = NULL;

    SECURITY_ATTRIBUTES securityAttributes;

    // Set the bInheritHandle flag so pipe handles are inherited.
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = TRUE;
    securityAttributes.lpSecurityDescriptor = NULL;

    // NOTE(Wuxiang): This must be big. Otherwise the script process would hang
    // when the buffer is fully filled.
    size_t processStdOutBufferSize = 1024 * 1024 * 16;

    // Create a pipe for the child process's STDOUT.
    if (!CreatePipe(&processStdOutReadHandle, &processStdOutWriteHandle, &securityAttributes, processStdOutBufferSize))
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API CreatePipe, Stdout. ") + GetLastErrorString());
    }

    // Ensure the read handle to the pipe for STDOUT is not inherited.
    if (!SetHandleInformation(processStdOutReadHandle, HANDLE_FLAG_INHERIT, 0))
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API SetHandleInformation, Stdout. ") + GetLastErrorString());
    }

    // Create the child process.
    wstring& processCmdWideStringTemp = const_cast<wstring&>(processCmdWideString);
    unsigned int processExitCode = StartProcessInternal(&processCmdWideStringTemp[0],
                                   processStdOutWriteHandle);

    // Read from pipe that is the standard output for child process.
    string processOutputString = ReadProcessOutPipe(processStdOutReadHandle);

    if (!CloseHandle(processStdOutReadHandle))
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API CloseHandle, StdOutRead. ") + GetLastErrorString());

    }

    if (!CloseHandle(processStdOutWriteHandle))
    {
        FALCON_ENGINE_THROW_API_EXCEPTION(string("Error: Windows API CloseHandle, StdOutWrite. ") + GetLastErrorString());
    }

    return make_pair(processExitCode, std::move(processOutputString));
}

std::pair<unsigned, std::string>
StartProcess(const std::string& processCmdString)
{
    std::wstring processCmdWideString(processCmdString.begin(), processCmdString.end());
    return StartProcess(processCmdWideString);
}

}

#endif
