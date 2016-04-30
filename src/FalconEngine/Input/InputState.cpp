#include <FalconEngine/Input/InputState.h>

namespace FalconEngine {
namespace Input {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
InputState::InputState()
    : m_keyboard(0)
    , m_mouse(0)
    , m_gamepad(0)
{

}

InputState::~InputState()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
std::shared_ptr<Keyboard> InputState::CreateKeyboard()
{
    if (m_keyboard)
    {
        return m_keyboard;
    }

    m_keyboard = std::make_shared<Keyboard>();
    m_keyboard->Initialize(false);
    return m_keyboard;

}

std::shared_ptr<Mouse> InputState::CreateMouse()
{
}

std::shared_ptr<Gamepad> InputState::CreateGamepad()
{
}


void InputState::HandleKeyboard()
{
}

}
}
