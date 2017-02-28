#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
MouseState::MouseState() :
    mPosition(),
    mWheelValue(0)
{
}


/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
MouseState::ButtonPressed(MouseButton button) const
{
    return mButtonTable.at(button).mPressed;
}

bool
MouseState::ButtonReleased(MouseButton button) const
{
    return !mButtonTable.at(button).mPressed;
}

bool
MouseState::ButtonDown(MouseButton button) const
{
    return mButtonTable.at(button).mDown;
}

bool
MouseState::ButtonUp(MouseButton button) const
{
    return mButtonTable.at(button).mUp;
}

void
MouseState::ButtonSetState(MouseButton button, bool pressed, double time)
{
    auto& buttonState = mButtonTable.at(button);
    auto buttonPressedCurrent = pressed;
    auto buttonPressedPrevious = buttonState.mPressed;

    // When just pressed.
    if (buttonPressedCurrent && !buttonPressedPrevious)
    {
        buttonState.mPressed = true;
        buttonState.mPressedMoment = time;

        buttonState.mDown = true;
        buttonState.mUp = false;
    }

    // When just released.
    else if (!buttonPressedCurrent && buttonPressedPrevious)
    {
        buttonState.mPressed = false;
        buttonState.mPressedMoment = 0;

        buttonState.mDown = false;
        buttonState.mUp = true;
    }

    // When still pressed.
    else if (buttonPressedCurrent /*&& buttonPressedPrevious*/)
    {
        // NOTE(Wuxiang): Need not modify the mPressedMoment.
        buttonState.mDown = false;
    }

    // When still released.
    else // (!buttonPressedCurrent && !buttonPressedPrevious)
    {
        buttonState.mUp = false;
    }

}

Vector2f
MouseState::GetPosition() const
{
    return mPosition;
}

void
MouseState::SetPosition(double x, double y, double time)
{
    auto mousePositionPrevious = mPosition;
    auto mousePositionCurrent = Vector2f(float(x), float(y));

    if (mousePositionCurrent != mousePositionPrevious)
    {
        mPositionDiff = mousePositionCurrent - mousePositionPrevious;
        mPosition = mousePositionCurrent;
    }
    else
    {
        mPositionDiff = Vector2f::Zero;
    }
}

Vector2f
MouseState::GetPositionDiff() const
{
    return mPositionDiff;
}

int
MouseState::GetWheelValue() const
{
    return mWheelValue;
}

int
MouseState::GetWheelValueDiff() const
{
    return mWheelValueDiff;
}

void
MouseState::SetWheelValue(double yoffset, double time)
{
    auto wheelValueCurrent = int(yoffset);
    auto wheelValuePrevious = mWheelValue;
    if (wheelValueCurrent != wheelValuePrevious)
    {
        mWheelValue = int(wheelValueCurrent);
        mWheelDirection = wheelValueCurrent < wheelValuePrevious
                          ? MouseWheelDirection::Down
                          : MouseWheelDirection::Up;

        mWheelValueDiff = wheelValueCurrent - wheelValuePrevious;
    }
    else
    {
        mWheelValue = 0;
        mWheelDirection = MouseWheelDirection::None;
        mWheelValueDiff = 0;
    }
}

}
