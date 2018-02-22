#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineSettings;

class KeyboardState;
using KeyboardStateSharedPtr = std::shared_ptr<KeyboardState>;

class MouseState;
using MouseStateSharedPtr = std::shared_ptr<MouseState>;

class PlatformGameEngineWindow;

FALCON_ENGINE_CLASS_BEGIN GameEngineInput
{
    friend class PlatformGameEngineWindow;

public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    FALCON_ENGINE_SINGLETON_SAFE_DECLARE(GameEngineInput);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEngineInput();

public:
    ~GameEngineInput();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    KeyboardState *
    GetKeyboardState() const;

    MouseState *
    GetMouseState() const;

    void
    Initialize();

    // @remark Update gets called once every frame by game engine.
    void
    UpdateFrame(double elasped);

private:
    void
    PollEventPlatform();

    void
    UpdateEvent(double elapsed);

private:
    KeyboardStateSharedPtr mKeyboardState;
    MouseStateSharedPtr    mMouseState;
};
FALCON_ENGINE_CLASS_END

}
