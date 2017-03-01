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
    GetKeyboardState() const
    {
        return mKeyboardState;
    }

    MouseStateSharedPtr
    GetMouseState() const
    {
        return mMouseState;
    }

    void
    Initialize(const GameEngineData *data, GameEngineSettingsSharedPtr settings);

private:
    void
    InitializePlatform(const GameEngineData *data);

    void
    DestroyPlatform();

private:
    GameEngineInputDispatcher       *mDispatcher;
    GameEngineInputSettingsSharedPtr mSettings;
    KeyboardStateSharedPtr           mKeyboardState;
    MouseStateSharedPtr              mMouseState;
};

}
