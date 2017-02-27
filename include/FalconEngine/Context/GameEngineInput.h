#pragma once

#include <FalconEngine/Context/ContextInclude.h>

#include <memory>
#include <vector>

#include <FalconEngine/Input/Mouse.h>
#include <FalconEngine/Input/MouseHandler.h>
#include <FalconEngine/Input/Keyboard.h>
#include <FalconEngine/Input/KeyboardHandler.h>

namespace FalconEngine
{

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
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEngineInput();
    ~GameEngineInput();

public:
    void
    Initialize(const GameEngineData *data, GameEngineInputSettingsSharedPtr settings);

    std::shared_ptr<Keyboard>
    CreateKeyboard();

    std::shared_ptr<Mouse>
    CreateMouse();

    void
    Update(float elapsed);

    std::shared_ptr<Keyboard>
    GetKeyboard() const
    {
        return mKeyboard;
    }

    std::shared_ptr<Mouse>
    GetMouse() const
    {
        return mMouseCurrent;
    }

    //// Keyboard Handling
    //void HandleKeyboard();
    //void RegisterKeyboardHandler(fnKeyboardHandler pHandler, void *caller = 0, size_t priority = IN_DEFAULT);
    //void UnregisterKeyboardHandler(fnKeyboardHandler pHandler);

    //// Mouse Handling
    //void HandleMouse();
    //void RegisterMouseHandler(fnMouseHandler pHandler, void *caller = 0, size_t priority = IN_DEFAULT);
    //void UnregisterMouseHandler(fnMouseHandler pHandler);
private:
    void
    InitializePlatform(const GameEngineData *data);

private:

    std::shared_ptr<Keyboard>   mKeyboard;
    std::shared_ptr<Mouse>      mMouse;

    std::vector<KeyboardHandlerPrototype> mKeyboard_handlers;
    std::vector<MouseHandler>     mMouse_handlers;

    float mLastUpdate;
    GameEngineInputSettingsSharedPtr mSettings;
    MouseState mMouseCurrent;
    MouseState mMousePrevious;
};

}
