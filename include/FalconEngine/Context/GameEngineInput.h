#pragma once

#include <FalconEngine/Context/Common.h>

#include <memory>
#include <vector>

namespace FalconEngine
{

class GameEngineData;
class GameEngineSettings;

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
    friend class GameEngineInputDispatcher;

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

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEngineInput();

public:
    ~GameEngineInput();

public:
    KeyboardState *
    GetKeyboardState() const;

    MouseState *
    GetMouseState() const;

public:
    void
    Initialize();

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
};
#pragma warning(default: 4251)

}
