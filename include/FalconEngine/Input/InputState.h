#pragma once

#include <memory>
#include <vector>

#include "Gamepad.h"
#include "GamepadHandler.h"
#include "Mouse.h"
#include "MouseHandler.h"
#include "Keyboard.h"
#include "KeyboardHandler.h"

namespace FalconEngine {


class InputState
{

public:

    InputState();
    ~InputState();

    std::shared_ptr<Keyboard>   CreateKeyboard();
    std::shared_ptr<Mouse>      CreateMouse();
    std::shared_ptr<Gamepad>    CreateGamepad();

    void Update(float deltaTime);

    std::shared_ptr<Keyboard>   GetKeyboard() const { return mKeyboard; }
    std::shared_ptr<Mouse>      GetMouse() const { return mMouse; }
    std::shared_ptr<Gamepad>    GetGamepad() const { return mGamepad; }

    // Keyboard Handling
    void HandleKeyboard();
    void RegisterKeyboardHandler(fnKeyboardHandler pHandler, void *caller = 0, size_t priority = IN_DEFAULT);
    void UnregisterKeyboardHandler(fnKeyboardHandler pHandler);

    // Mouse Handling
    void HandleMouse();
    void RegisterMouseHandler(fnMouseHandler pHandler, void *caller = 0, size_t priority = IN_DEFAULT);
    void UnregisterMouseHandler(fnMouseHandler pHandler);

    // Gamepad Handling
    void HandleGamepad();
    void RegisterGamepadHandler(fnGamepadHandler pHandler, void *caller = 0, size_t priority = IN_DEFAULT);
    void UnregisterGamepadHandler(fnGamepadHandler pHandler);

private:

    std::shared_ptr<Keyboard>   mKeyboard;
    std::shared_ptr<Mouse>      mMouse;
    std::shared_ptr<Gamepad>    mGamepad;

    std::vector<keyboard_handler> mKeyboard_handlers;
    std::vector<MouseHandler>     mMouse_handlers;
    std::vector<gamepad_handler>  mGamepad_handlers;

    enum InputDeviceType {
        KEYBOARD,
        MOUSE
    };

    float mLastUpdate;
};

}
}
