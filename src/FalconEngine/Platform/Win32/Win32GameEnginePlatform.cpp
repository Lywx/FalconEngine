#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineDebugger.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Platform/Win32/Common.h>
namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    // NOTE(Wuxiang): You have to initialize OpenGL context first.
    InitializeWindowPlatform();
    // InitializeLoaderPlatform();
}

void
GameEnginePlatform::InitializeContextPlatform()
{
}

void
GameEnginePlatform::InitializeWindowPlatform()
{
    auto gameEngineSettings = GameEngineSettings::GetInstance();
    auto gameEngineData = GameEngineData::GetInstance();


    // Register class and create window
    {
        // Register class
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, L"IDI_ICON");
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"SnowmanWindowClass";
        wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
        if (!RegisterClassEx(&wcex))
        {
            return 1;
        }

        // Create window
        int w, h;
        g_game->GetDefaultSize(w, h);

        RECT rc;
        rc.top = 0;
        rc.left = 0;
        rc.right = static_cast<LONG>(w);
        rc.bottom = static_cast<LONG>(h);

        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        HWND hwnd = CreateWindowEx(0, L"SnowmanWindowClass", L"Snowman", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                nullptr);
        // TODO: Change to CreateWindowEx(WS_EX_TOPMOST, L"SnowmanWindowClass", L"Snowman", WS_POPUP,
        // to default to fullscreen.

        if (!hwnd)
        {
            return 1;
        }

        ShowWindow(hwnd, nCmdShow);
        // TODO: Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_game.get()));

        GetClientRect(hwnd, &rc);
    }

    auto window = std::make_shared<GameEngineWindow>(windowHandle);
    window->Initialize();
    gameEngineData->mWindow = window;
}

}

#endif
