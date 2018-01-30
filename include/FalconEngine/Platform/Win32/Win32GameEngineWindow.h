#pragma once

#include <FalconEngine/Core/Common.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
namespace FalconEngine
{

class GameEngineInput;
class GameEngineSettings;

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
FALCON_ENGINE_CLASS_BEGIN GameEngineWindow
{
public:
    explicit GameEngineWindow();
    ~GameEngineWindow() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    InitializeInputPlatform();

private:
    GameEngineInput    *mInput;
    GameEngineSettings *mSettings;
};
FALCON_ENGINE_CLASS_END

}

#endif