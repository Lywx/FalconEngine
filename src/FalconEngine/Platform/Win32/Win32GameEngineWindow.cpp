#include <FalconEngine/Platform/Win32/Win32GameEngineWindow.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/Timer.h>
#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Input/KeyState.h>
#include <FalconEngine/Input/MouseState.h>

#include <Windows.h>
#include <Windowsx.h>

namespace FalconEngine
{

Key
GetKey(WPARAM wParam)
{
    auto key = Key::Unknown;
    switch (wParam)
    {
    case VK_MENU:
    {
        // TODO(Wuxiang): Test this.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/gg153546(v=vs.85).aspx
        if (GetKeyState(VK_LMENU) & 0x8000)
        {
            key = Key::LeftAlt;
        }
        else
        {
            key = Key::RightAlt;
        }
    }
    break;

    case VK_CONTROL:
    {
        if (GetKeyState(VK_LCONTROL) & 0x8000)
        {
            key = Key::LeftControl;
        }
        else
        {
            key = Key::RightControl;
        }
    }
    break;

    case VK_SHIFT:
    {
        if (GetKeyState(VK_LSHIFT) & 0x8000)
        {
            key = Key::LeftShift;
        }
        else
        {
            key = Key::RightShift;
        }
    }
    break;

    default:
        key = Key(wParam);
    }

    return key;
}

LRESULT CALLBACK
GameEngineWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static bool s_in_sizemove = false;
    static bool s_in_suspend = false;
    static bool s_minimized = false;
    // TODO: Set s_fullscreen to true if defaulting to fullscreen.
    static bool s_fullscreen = false;

    auto gameEngineWindow = reinterpret_cast<PlatformGameEngineWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    auto gameEngineSettings = GameEngineSettings::GetInstance();

    switch (message)
    {
    // NOTE(Wuxiang): Input messages.
    case WM_KEYDOWN:
    {
        gameEngineWindow->ProcessKeyEvent(GetKey(wParam), message == WM_KEYDOWN);
    }
    break;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    {
        gameEngineWindow->ProcessMouseButtonEvent(MouseButton::LeftButton, message == WM_LBUTTONDOWN);
    }
    break;

    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    {
        gameEngineWindow->ProcessMouseButtonEvent(MouseButton::MiddleButton, message == WM_MBUTTONDOWN);
    }
    break;

    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    {
        gameEngineWindow->ProcessMouseButtonEvent(MouseButton::RightButton, message == WM_RBUTTONDOWN);
    }
    break;

    case WM_MOUSEMOVE:
    {
        auto x = double(GET_X_LPARAM(lParam));
        auto y = double(GET_Y_LPARAM(lParam));

        gameEngineWindow->ProcessMouseMoveEvent(x, y);
    }
    break;

    case WM_SYSKEYDOWN:
        if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
        {
            // Implements the classic ALT+ENTER fullscreen toggle
            if (s_fullscreen)
            {
                SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
                SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

                int width = gameEngineSettings->mWindowWidth;
                int height = gameEngineSettings->mWindowHeight;

                ShowWindow(hWnd, SW_SHOWNORMAL);
                SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
            }
            else
            {
                SetWindowLongPtr(hWnd, GWL_STYLE, 0);
                SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

                SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                ShowWindow(hWnd, SW_SHOWMAXIMIZED);
            }

            s_fullscreen = !s_fullscreen;
        }
        break;

    // NOTE(Wuxiang): Game update messages.
    case WM_PAINT:
        if (s_in_sizemove && gameEngineWindow)
        {
            // TODO(Wuxiang): I think the game is not running 60 frames per second.
            //game->Tick();
        }
        else
        {
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
        {
            if (!s_minimized)
            {
                s_minimized = true;
                if (!s_in_suspend && gameEngineWindow)
                {
                    gameEngineWindow->OnSuspending();
                }
                s_in_suspend = true;
            }
        }
        else if (s_minimized)
        {
            s_minimized = false;
            if (s_in_suspend && gameEngineWindow)
            {
                gameEngineWindow->OnResuming();
            }
            s_in_suspend = false;
        }
        else if (!s_in_sizemove && gameEngineWindow)
        {
            auto width = int(LOWORD(lParam));
            auto height = int(HIWORD(lParam));
            gameEngineWindow->OnSizeChanged(width, height);
        }
        break;

    case WM_ENTERSIZEMOVE:
        s_in_sizemove = true;
        break;

    case WM_EXITSIZEMOVE:
        s_in_sizemove = false;
        if (gameEngineWindow)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);

            gameEngineWindow->OnSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
        }
        break;

    case WM_GETMINMAXINFO:
    {
        auto info = reinterpret_cast<MINMAXINFO *>(lParam);
        info->ptMinTrackSize.x = 320;
        info->ptMinTrackSize.y = 200;
    }
    break;

    case WM_ACTIVATEAPP:
        if (gameEngineWindow)
        {
            if (wParam)
            {
                gameEngineWindow->OnActivated();
            }
            else
            {
                gameEngineWindow->OnDeactivated();
            }
        }
        break;

    case WM_POWERBROADCAST:
        switch (wParam)
        {
        case PBT_APMQUERYSUSPEND:
            if (!s_in_suspend && gameEngineWindow)
            {
                gameEngineWindow->OnSuspending();
            }
            s_in_suspend = true;
            return TRUE;

        case PBT_APMRESUMESUSPEND:
            if (!s_minimized)
            {
                if (s_in_suspend && gameEngineWindow)
                {
                    gameEngineWindow->OnResuming();
                }
                s_in_suspend = false;
            }
            return TRUE;
        }
        break;

    // NOTE(Wuxiang): Game exit messages.
    case WM_CLOSE:
        gameEngineWindow->OnClose();
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MENUCHAR:
        // A menu is active and the user presses a key that does not correspond
        // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
        return MAKELRESULT(0, MNC_CLOSE);

    default:
        ;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformGameEngineWindow::PlatformGameEngineWindow(const HWND & handle) :
    mHandle(handle),
    mData(nullptr),
    mInput(nullptr),
    mSettings(nullptr)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformGameEngineWindow::Initialize()
{
    InitializeData();
    InitializePlatform();
}

void
PlatformGameEngineWindow::ProcessKeyEvent(Key key, bool keyPressed)
{
    mInput->mKeyboardState->SetKeyInternal(key, keyPressed, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::ProcessMouseButtonEvent(MouseButton button, bool buttonPressed)
{
    mInput->mMouseState->SetButtonInternal(MouseButton(button), buttonPressed, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::ProcessMouseMoveEvent(double x, double y)
{
    // NOTE(Wuxiang): I invert the Y coordinate of screen space so that (0, 0)
    // as left lower corner to be consistent with the OpenGL NDC convention.
    mInput->mMouseState->SetPositionInternal(x, mSettings->mWindowHeight - y, Timer::GetMilliseconds());
}

void
PlatformGameEngineWindow::OnActivated()
{
}

void
PlatformGameEngineWindow::OnDeactivated()
{
}

void
PlatformGameEngineWindow::OnSuspending()
{
}

void
PlatformGameEngineWindow::OnResuming()
{
}

void
PlatformGameEngineWindow::OnSizeChanged(int width, int height)
{
    _UNUSED(width);
    _UNUSED(height);
}

void
PlatformGameEngineWindow::OnClose()
{
    mData->mRunning = false;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformGameEngineWindow::InitializeData()
{
    mData = GameEngineData::GetInstance();
    mInput = GameEngineInput::GetInstance();
    mSettings = GameEngineSettings::GetInstance();
}

void
PlatformGameEngineWindow::InitializePlatform()
{
    // SetWindowLongPtr(mHandle, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(GameEngineWindowProcess));
}

}

#endif