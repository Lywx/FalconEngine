#pragma once

#include <FalconEngine/Context/Header.h>

#include <memory>
#include <vector>

namespace FalconEngine
{

class GameEngineData;
using GameEngineDataSharedPtr = std::shared_ptr<GameEngineData>;

class GameEngineSettings;
using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;

class KeyboardState;
using KeyboardStateSharedPtr = std::shared_ptr<KeyboardState>;

class MouseState;
using MouseStateSharedPtr = std::shared_ptr<MouseState>;

class GameEngineInputDispatcher;
class GameEngineInputDispatcherDeleter
{
public:
    void operator()(GameEngineInputDispatcher *inputDispatcher);
};

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineInput
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

    MouseStateSharedPtr
    GetMouseState() const;

public:
    void
    Initialize(GameEngineDataSharedPtr gameEngineData, GameEngineSettingsSharedPtr gameEngineSettings);

    // @remark Update gets called every frame by game engine.
    void
    Update();

private:
    void
    InitializePlatform();

    void
    DestroyPlatform();

    void
    PollEvent();

    void
    UpdateEvent();

private:
    std::unique_ptr<GameEngineInputDispatcher, GameEngineInputDispatcherDeleter> mDispatcher;

    KeyboardStateSharedPtr                                                       mKeyboardState;
    MouseStateSharedPtr                                                          mMouseState;

    GameEngineDataSharedPtr                                                      mGameEngineData;
    GameEngineSettingsSharedPtr                                                  mGameEngineSettings;
};
#pragma warning(default: 4251)

}
