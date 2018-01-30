#pragma once

#include <FalconEngine/Core/Common.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Input/MouseButton.h>
#include <FalconEngine/Platform/Win32/Common.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineInput;
class GameEngineSettings;

enum class Key;

LRESULT CALLBACK
GameEngineWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
FALCON_ENGINE_CLASS_BEGIN GameEngineWindow
{
public:
    explicit GameEngineWindow(const HWND & handle);
    ~GameEngineWindow() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

    void
    ProcessKeyEvent(Key key, bool pressed);

    void
    ProcessMouseButtonEvent(MouseButton button, bool buttonPressed);

    void
    ProcessMouseMoveEvent(double x, double y);

    void
    OnActivated();

    void
    OnDeactivated();

    void
    OnSuspending();

    void
    OnResuming();

    void
    OnSizeChanged(int width, int height);

    void
    OnClose();

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    InitializeData();

    void
    InitializePlatform();

public:
    HWND mHandle;

private:
    GameEngineData     *mData;
    GameEngineInput    *mInput;
    GameEngineSettings *mSettings;
};
FALCON_ENGINE_CLASS_END

}

#endif