#include <FalconEngine/Input/MouseState.h>
#include <FalconEngine/Context/GameTimer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
MouseState::MouseState() :
    mPosition(),
    mWheelValue(0),
    mWheelValueDiff(0)
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
MouseState::SetButtonInternal(MouseButton button, bool buttonPressed, double timeCurrent)
{
    auto& buttonState = mButtonTable.at(button);
    buttonState.mButtonChanged = true;

    auto buttonPressedCurrent = buttonPressed;
    auto buttonPressedPrevious = buttonState.mPressed;

    UpdateButton(buttonState, buttonPressedCurrent, buttonPressedPrevious, timeCurrent);
}

Vector2f
MouseState::GetPosition() const
{
    return mPosition;
}

void
MouseState::SetPositionInternal(double x, double y, double /* timeCurrent */)
{
    mPositionChanged = true;

    auto mousePositionPrevious = mPosition;
    auto mousePositionCurrent = Vector2f(float(x), float(y));

    UpdatePosition(mousePositionCurrent, mousePositionPrevious);
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
MouseState::SetWheelValueInternal(double yoffset, double /* timeCurrent */)
{
    mWheelValueChanged = true;

    auto wheelValueCurrent = int(yoffset);
    auto wheelValuePrevious = mWheelValue;
    UpdateWheelValue(wheelValueCurrent, wheelValuePrevious);
}

void
MouseState::UpdateEvent(double /* elapsed */)
{
    if (!mPositionChanged)
    {
        // NOTE(Wuxiang): The event polling has not polled anything reflecting
        // position changes. So the position is not changed. We have to reset
        // position difference.
        UpdatePosition(mPosition, mPosition);
    }
    else
    {
        // Reset change flag if there has been changes during this frame.
        mPositionChanged = false;
    }

    // Same idea as above.
    if (!mWheelValueChanged)
    {
        UpdateWheelValue(mWheelValue, mWheelValue);
    }
    else
    {
        mWheelValueChanged = false;
    }

    // Same idea as above.
    for (auto& buttonStatePair : mButtonTable)
    {
        auto& buttonState = buttonStatePair.second;
        if (!buttonState.mButtonChanged)
        {
            UpdateButton(buttonState,
                         buttonState.mPressed,
                         buttonState.mPressed,
                         GameTimer::GetMilliseconds());
        }
        else
        {
            buttonState.mButtonChanged = false;
        }
    }
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
MouseState::UpdateButton(MouseButtonState& buttonState,
                         bool              buttonPressedCurrent,
                         bool              buttonPressedPrevious,
                         double            timeCurrent)
{
    // When just pressed.
    if (buttonPressedCurrent && !buttonPressedPrevious)
    {
        Debug::OutputString("K");

        buttonState.mPressed = true;
        buttonState.mPressedMoment = timeCurrent;

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
        buttonState.mUp = false;
    }

    // When still released.
    else // (!buttonPressedCurrent && !buttonPressedPrevious)
    {
        buttonState.mUp = false;
        buttonState.mDown = false;
    }
}

void
MouseState::UpdatePosition(Vector2f mousePositionCurrent, Vector2f mousePositionPrevious)
{
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

void
MouseState::UpdateWheelValue(int wheelValueCurrent, int wheelValuePrevious)
{
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
