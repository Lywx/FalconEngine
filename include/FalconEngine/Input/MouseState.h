#pragma once

#include <FalconEngine/InputInclude.h>
#include <FalconEngine/Input/MouseButtonState.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

enum class MouseWheelDirection
{
    None = 0,
    Down = 1,
    Up = 2
};

class MouseState sealed
{
public:
    MouseState();
    ~MouseState() = default;

public:
    bool
    ButtonPressed(MouseButton button) const;

    bool
    ButtonReleased(MouseButton button) const;

    bool
    ButtonDown(MouseButton button) const;

    bool
    ButtonUp(MouseButton button) const;

    void
    ButtonSetState(MouseButton button, bool pressed, double time);

    Vector2f
    GetPosition() const;

    void
    SetPosition(double x, double y, double time);

    Vector2f
    GetPositionDiff() const;

    int
    GetWheelValue() const;

    int
    GetWheelValueDiff() const;

    void
    SetWheelValue(double yoffset, double time);

private:
    MouseButtonStateMap mButtonTable;
    Vector2f            mPosition;
    Vector2f            mPositionDiff;
    MouseWheelDirection mWheelDirection = MouseWheelDirection::None;
    int                 mWheelValue;
    int                 mWheelValueDiff;
};

}
