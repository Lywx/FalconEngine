#include <FalconEngine/Input/MouseButtonState.h>

#include <vector>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
MouseButtonState::MouseButtonState() :
    mButton(MouseButton::Unknown),
    mPressed(false),
    mDown(false),
    mUp(false)
{
}

MouseButtonState::MouseButtonState(MouseButton button) :
    mButton(button),
    mPressed(false),
    mDown(false),
    mUp(false)
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
MouseButtonStateMap::MouseButtonStateMap()
{
    static std::vector<MouseButton> sButtons = { MouseButton::LeftButton, MouseButton::RightButton, MouseButton::MiddleButton };

    int buttonNum = int(sButtons.size());
    for (int buttonIndex = 0; buttonIndex < buttonNum; ++buttonIndex)
    {
        auto button = sButtons[buttonIndex];
        insert({ button, MouseButtonState(button) });
    }
}

}
