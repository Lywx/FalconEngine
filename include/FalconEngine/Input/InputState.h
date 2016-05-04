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

    std::shared_ptr<Keyboard>   GetKeyboard() const { return m_keyboard; }
    std::shared_ptr<Mouse>      GetMouse() const { return m_mouse; }
    std::shared_ptr<Gamepad>    GetGamepad() const { return m_gamepad; }

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

    std::shared_ptr<Keyboard>   m_keyboard;
    std::shared_ptr<Mouse>      m_mouse;
    std::shared_ptr<Gamepad>    m_gamepad;

    std::vector<keyboard_handler> m_keyboard_handlers;
    std::vector<MouseHandler>     m_mouse_handlers;
    std::vector<gamepad_handler>  m_gamepad_handlers;

    enum InputDeviceType {
        KEYBOARD,
        MOUSE
    };

    float m_lastUpdate;
};

}
}
