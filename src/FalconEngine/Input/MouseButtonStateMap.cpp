#include <FalconEngine/Input/MouseButtonState.h>

namespace FalconEngine
{

MouseButtonState::MouseButtonState(MouseButton button) :
    mButton(button),
    mPressed(false),
    mDown(false),
    mUp(false)
{
}

MouseButtonStateMap::MouseButtonStateMap()
{
    static std::vector<MouseButton> sButtons = { MouseButton::LeftButton, MouseButton::RightButton, MouseButton::MiddleButton };
    for (int i = 0; i < sButtons.size(); ++i)
    {
        auto button = sButtons[i];
        insert({ button, MouseButtonState(button) });
    }
}

}
