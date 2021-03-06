#include <FalconEngine/Core/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Platform/Win32/Win32GameEngineWindow.h>
#include <FalconEngine/Platform/Win32/Win32Utility.h>

#include <Windows.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DGameEnginePlatformData.h>
#elif defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLGameEnginePlatformData.h>
#endif

namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    InitializeDataPlatform();

    // NOTE(Wuxiang): Win32 would need to create window first, then create context.
    InitializeWindowPlatform();
    InitializeContextPlatform();
}

void
GameEnginePlatform::InitializeWindowPlatform()
{
    auto gameEngineSettings = GameEngineSettings::GetInstance();

    HMODULE moduleHandle = GetModuleHandle(nullptr);

    // Register window class.
    auto windowClassName = "FalconEngineGameWindowClass";
    {
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);

        // https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
        // Redraws the entire window if a movement or
        // size adjustment changes the width of the client area.
        wcex.style = CS_HREDRAW
                     // Redraws the entire window if a movement or
                     // size adjustment changes the height of the client area.
                     | CS_VREDRAW;

        wcex.lpfnWndProc = GameEngineWindowProcess;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = moduleHandle;
        wcex.hIcon = nullptr;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = windowClassName;
        wcex.hIconSm = nullptr;

        if (!RegisterClassEx(&wcex))
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Window class register failed: " + GetLastErrorString());
        }
    }

    // Create window.
    HWND windowHandle;
    {
        RECT rect;
        rect.top = 0;
        rect.left = 0;
        rect.right = static_cast<LONG>(gameEngineSettings->mWindowWidth);
        rect.bottom = static_cast<LONG>(gameEngineSettings->mWindowHeight);
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        // TODO: Change to CreateWindowEx(WS_EX_TOPMOST, "", "", WS_POPUP,
        // to default to fullscreen.
        windowHandle = CreateWindowEx(
                           0,                                        //_In_     DWORD     dwExStyle,
                           windowClassName,                          //_In_opt_ LPCTSTR   lpClassName,
                           gameEngineSettings->mWindowTitle.c_str(), //_In_opt_ LPCTSTR   lpWindowName,
                           WS_OVERLAPPEDWINDOW,                      //_In_     DWORD     dwStyle,
                           CW_USEDEFAULT,                            //_In_     int       x,
                           CW_USEDEFAULT,                            //_In_     int       y,
                           rect.right - rect.left,                   //_In_     int       nWidth,
                           rect.bottom - rect.top,                   //_In_     int       nHeight,
                           nullptr,                                  //_In_opt_ HWND      hWndParent,
                           nullptr,                                  //_In_opt_ HMENU     hMenu,
                           moduleHandle,                             //_In_opt_ HINSTANCE hInstance,
                           nullptr                                   //_In_opt_ LPVOID    lpParam
                       );

        if (!windowHandle)
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Window creation failed: " + GetLastErrorString());
        }

        // TODO: Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.
        ShowWindow(windowHandle, SW_SHOW);


        GetClientRect(windowHandle, &rect);
    }

    mWindow = std::make_shared<PlatformGameEngineWindow>(windowHandle);
    mWindow->Initialize();

    SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(mWindow.get()));
}

}

#endif
