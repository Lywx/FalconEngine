#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Input/MouseButtonState.h>
#include <FalconEngine/Math/Vector2.h>
#include "FalconEngine/Math/Vector3.h"

namespace FalconEngine
{

enum class MouseWheelDirection
{
    None = 0,
    Down = 1,
    Up = 2
};

class FALCON_ENGINE_API MouseState final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    MouseState();
    ~MouseState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    bool
    ButtonPressed(MouseButton button) const;

    bool
    ButtonReleased(MouseButton button) const;

    bool
    ButtonDown(MouseButton button) const;

    bool
    ButtonUp(MouseButton button) const;

    // @return Mouse position in the window space. Bottom-left of window as (0, 0).
    Vector2f
    GetPosition() const;

    Vector2f
    GetPositionDiff() const;

    int
    GetWheelValue() const;

    int
    GetWheelValueDiff() const;

// internal
public:
    /************************************************************************/
    /* Internal Members                                                     */
    /************************************************************************/
    void
    SetButtonInternal(MouseButton button, bool buttonPressed, double timeCurrent);

    void
    SetPositionInternal(double x, double y, double timeCurrent);

    void
    SetWheelValueInternal(double yoffset, double timeCurrent);

    void
    UpdateEvent(double elapsed);

private:
    void
    UpdateButton(MouseButtonState& buttonState,
                 bool              buttonPressedCurrent,
                 bool              buttonPressedPrevious,
                 double            timeCurrent);

    void
    UpdatePosition(Vector2f mousePositionCurrent, Vector2f mousePositionPrevious);

    void
    UpdateWheelValue(int wheelValueCurrent, int wheelValuePrevious);

private:
    MouseButtonStateMap mButtonTable;
    Vector2f            mPosition;
    bool                mPositionChanged = false;
    Vector2f            mPositionDiff;

    MouseWheelDirection mWheelDirection = MouseWheelDirection::None;
    int                 mWheelValue;
    bool                mWheelValueChanged = false;
    int                 mWheelValueDiff;
};

}
