#include <FalconEngine/Platform/Win32/Win32GameEngineWindow.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Platform/Win32/Common.h>

namespace FalconEngine
{

LRESULT CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static bool s_in_sizemove = false;
    static bool s_in_suspend = false;
    static bool s_minimized = false;
    static bool s_fullscreen = false;
    // TODO: Set s_fullscreen to true if defaulting to fullscreen.

    auto game = reinterpret_cast<GameEngineWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    auto gameInput = GameInput::GetInstance();

    switch (message)
    {
    // NOTE(Wuxiang): Game input messages.
    case WM_KEYDOWN:
    {
        auto key = Key(unsigned int(wParam));
        gameInput->GetKeyboardState()->SetKeyInternal(key, true, Timer::GetMilliseconds());
    }
    break;

    case WM_KEYUP:
    {
        auto key = Key(unsigned int(wParam));
        gameInput->GetKeyboardState()->SetKeyInternal(key, false, Timer::GetMilliseconds());
    }
    break;

    case WM_MOUSEMOVE:
    {
        auto x = GET_X_LPARAM(lParam);
        auto y = GET_Y_LPARAM(lParam);

        gameInput->GetMouseState()->SetPositionInternal(x, y, Timer::GetMilliseconds());
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

                int width = 800;
                int height = 600;
                if (game)
                {
                    game->GetDefaultSize(width, height);
                }

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
        if (s_in_sizemove && game)
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
                if (!s_in_suspend && game)
                {
                    game->OnSuspending();
                }
                s_in_suspend = true;
            }
        }
        else if (s_minimized)
        {
            s_minimized = false;
            if (s_in_suspend && game)
            {
                game->OnResuming();
            }
            s_in_suspend = false;
        }
        else if (!s_in_sizemove && game)
        {
            game->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
        }
        break;

    case WM_ENTERSIZEMOVE:
        s_in_sizemove = true;
        break;

    case WM_EXITSIZEMOVE:
        s_in_sizemove = false;
        if (game)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);

            game->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
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
        if (game)
        {
            if (wParam)
            {
                game->OnActivated();
            }
            else
            {
                game->OnDeactivated();
            }
        }
        break;

    case WM_POWERBROADCAST:
        switch (wParam)
        {
        case PBT_APMQUERYSUSPEND:
            if (!s_in_suspend && game)
            {
                game->OnSuspending();
            }
            s_in_suspend = true;
            return TRUE;

        case PBT_APMRESUMESUSPEND:
            if (!s_minimized)
            {
                if (s_in_suspend && game)
                {
                    game->OnResuming();
                }
                s_in_suspend = false;
            }
            return TRUE;
        }
        break;

    // NOTE(Wuxiang): Game exit messages.
    case WM_CLOSE:
        game->Exit();
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
GameEngineWindow::GameEngineWindow() : mInput(nullptr), mSettings(nullptr)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineWindow::InitializeInputPlatform()
{
}

}

#endif