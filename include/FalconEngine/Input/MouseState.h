#pragma once

#include <FalconEngine/Input/Common.h>

#include <FalconEngine/Input/MouseButtonState.h>
#include <FalconEngine/Math/Vector2.h>
#include "FalconEngine/Math/Vector3.h"

namespace FalconEngine
{

enum class FALCON_ENGINE_API MouseWheelDirection
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

    void
    UpdatePosition(Vector2f mousePositionPrevious, Vector2f mousePositionCurrent);

    Vector2f
    GetPositionDiff() const;

    int
    GetWheelValue() const;

    int
    GetWheelValueDiff() const;

    void
    UpdateWheelValue(int wheelValueCurrent, int wheelValuePrevious);

// internal
public:
    /************************************************************************/
    /* Internal Members                                                     */
    /************************************************************************/
    void
    SetButtonInternal(MouseButton button, bool pressed, double time);

    void
    SetPositionInternal(double x, double y, double time);

    void
    SetWheelValueInternal(double yoffset, double time);

    void
    UpdateEvent();

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
