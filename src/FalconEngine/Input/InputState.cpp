#include <FalconEngine/Input/InputState.h>

namespace FalconEngine {
namespace Input {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
InputState::InputState()
    : mKeyboard(0)
    , mMouse(0)
    , mGamepad(0)
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
    if (mKeyboard)
    {
        return mKeyboard;
    }

    mKeyboard = std::make_shared<Keyboard>();
    mKeyboard->Initialize(false);
    return mKeyboard;

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
