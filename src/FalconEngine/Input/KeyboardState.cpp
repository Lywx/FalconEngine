#include <FalconEngine/Input/KeyboardState.h>
#include <FalconEngine/Core/Timer.h>

namespace FalconEngine
{

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
KeyboardState::KeyDown(Key key) const
{
    return at(key).mDown;
}

bool
KeyboardState::KeyPressed(Key key) const
{
    return at(key).mPressed;
}

bool
KeyboardState::KeyReleased(Key key) const
{
    return !at(key).mPressed;
}

bool
KeyboardState::KeyUp(Key key) const
{
    return at(key).mUp;
}

void
KeyboardState::SetKeyInternal(Key key, bool kepPressed, double timeCurrent)
{
    auto keyPressedPrevious = at(key).mPressed;
    auto keyPressedCurrent = kepPressed;
    auto& keyState = at(key);
    keyState.mKeyChanged = true;

    UpdateKey(keyState, keyPressedCurrent, keyPressedPrevious, timeCurrent);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
KeyboardState::UpdateEvent(double /* elapsed */)
{
    for (auto& keyStatePair : *this)
    {
        auto& keyState = keyStatePair.second;

        // NOTE(Wuxiang): The event polling has not polled anything reflecting
        // position changes. So the position is not changed. We have to reset
        // position difference.
        if (!keyState.mKeyChanged)
        {
            UpdateKey(keyState,
                      keyState.mPressed,
                      keyState.mPressed,
                      Timer::GetMilliseconds());
        }
        else
        {
            // Reset change flag if there has been changes during this frame.
            keyState.mKeyChanged = false;
        }
    }
}

void
KeyboardState::UpdateKey(KeyState& keyState,
                         bool      keyPressedCurrent,
                         bool      keyPressedPrevious,
                         double    timeCurrent)
{
    // When just pressed.
    if (keyPressedCurrent && !keyPressedPrevious)
    {
        keyState.mPressed = true;
        keyState.mPressedMoment = timeCurrent;

        keyState.mDown = true;
        keyState.mUp = false;
    }

    // When just released.
    else if (!keyPressedCurrent && keyPressedPrevious)
    {
        keyState.mPressed = false;
        keyState.mPressedMoment = 0;

        keyState.mDown = false;
        keyState.mUp = true;
    }

    // When still pressed.
    else if (keyPressedCurrent /*&& keyPressedPrevious*/)
    {
        // NOTE(Wuxiang): Need not modify the mPressedMoment.
        keyState.mDown = false;
        keyState.mUp = false;
    }

    // When still released.
    else // (!keyPressedCurrent && !keyPressedPrevious)
    {
        keyState.mDown = false;
        keyState.mUp = false;
    }
}

}
