#pragma once

#include <FalconEngine/ContextInclude.h>

#include <memory>
#include <vector>

namespace FalconEngine
{

class GameEngineSettings;
using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;

class GameEngineInputSettings;
using GameEngineInputSettingsSharedPtr = std::shared_ptr<GameEngineInputSettings>;

class KeyboardState;
using KeyboardStateSharedPtr = std::shared_ptr<KeyboardState>;

class MouseController;
using MouseControllerSharedPtr = std::shared_ptr<MouseController>;;

class MouseState;
using MouseStateSharedPtr = std::shared_ptr<MouseState>;

class GameEngineData;
class GameEngineInput
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEngineInput *
    GetInstance()
    {
        static GameEngineInput sInstance;
        return &sInstance;
    }

public:
    friend class GameEngineInputDispatcher;

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEngineInput();
    ~GameEngineInput();

public:
    KeyboardStateSharedPtr
    GetKeyboardState() const;

    MouseControllerSharedPtr
    GetMouseController() const;

    MouseStateSharedPtr
    GetMouseState() const;

internal:
    void
    Initialize(const GameEngineData *data, GameEngineSettingsSharedPtr settings);

    // @remark Update gets called every frame by game engine.
    void
    Update();

private:
    void
    InitializePlatform(const GameEngineData *data);

    void
    DestroyPlatform();

    void
    PollEvent();

    void
    UpdateEvent();

private:
    GameEngineInputDispatcher       *mDispatcher;
    GameEngineInputSettingsSharedPtr mSettings;
    KeyboardStateSharedPtr           mKeyboardState;
    MouseControllerSharedPtr         mMouseController;
    MouseStateSharedPtr              mMouseState;
};

}
