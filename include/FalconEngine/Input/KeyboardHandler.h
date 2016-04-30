#pragma once

#include <memory>

#include "InputHandler.h"
#include "Keyboard.h"

namespace FalconEngine {
namespace Input {

typedef bool(*KeyboardHandler)(std::shared_ptr<Keyboard> pKeyboard, void *userData);

class keyboard_handler : public InputHandler
{
    bool m_Enabled;

public:
    KeyboardHandler m_pHandler;
    keyboard_handler()
        : InputHandler()
        , m_pHandler(0)
        , m_Enabled(true)
    {}

    void Enable(bool enabled) { m_Enabled = enabled; }
    bool IsEnabled() const { return m_Enabled; }
};

}
}
