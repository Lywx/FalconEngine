#pragma once

#include <FalconEngine/Context/ContextInclude.h>

#include <memory>
#include <vector>

#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Input/KeyboardState.h>

namespace FalconEngine
{

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
