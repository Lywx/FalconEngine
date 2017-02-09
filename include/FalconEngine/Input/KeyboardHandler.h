#pragma once

#include <memory>

#include "InputHandler.h"
#include "Keyboard.h"

namespace FalconEngine {


typedef bool(*KeyboardHandler)(std::shared_ptr<Keyboard> pKeyboard, void *userData);

class keyboard_handler : public InputHandler
{
    bool m_Enabled;

public:
    KeyboardHandler mPHandler;
    keyboard_handler()
        : InputHandler()
        , mPHandler(0)
        , m_Enabled(true)
    {}

    void Enable(bool enabled) { m_Enabled = enabled; }
    bool IsEnabled() const { return m_Enabled; }
};

}
}
