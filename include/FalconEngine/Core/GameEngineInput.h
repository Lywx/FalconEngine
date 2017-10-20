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

class GameEngineWindow;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineInput
{
    friend class GameEngineWindow;

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
    PollEvent();

    void
    UpdateEvent(double elapsed);

private:
    KeyboardStateSharedPtr mKeyboardState;
    MouseStateSharedPtr    mMouseState;
};
#pragma warning(default: 4251)

}
