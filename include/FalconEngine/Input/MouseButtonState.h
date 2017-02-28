#pragma once

#include <FalconEngine/Input/InputInclude.h>
#include <FalconEngine/Input/MouseButton.h>

#include <unordered_map>

namespace FalconEngine
{

enum class MouseButtonPressState
{
    Pressed,
    Released,
};

class MouseButtonState sealed
{
public:
    explicit MouseButtonState(MouseButton button);
    ~MouseButtonState() = default;

public:
    MouseButton mButton;
    bool        mPressed;
    double      mPressedMoment = 0;   // Millisecond time stamp.
    bool        mDown;                // Transition from being released to being pressed.
    bool        mUp;                  // Transition from being pressed to being released.
};

class MouseButtonStateMap : public std::unordered_map<MouseButton, MouseButtonState>
{
public:
    MouseButtonStateMap();
};

}
