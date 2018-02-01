#pragma once

#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0601
#include <SDKDDKVer.h>

// Prevents Windows headers from defining macros called min and max, which
// conflict with identifiers in the C++ standard library.
#define NOMINMAX

#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <comdef.h>
#include <windows.h>
#include <Windowsx.h>

#include <FalconEngine/Platform/Win32/Win32LibClean.h>