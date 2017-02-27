#pragma once

#include <FalconEngine/Input/InputInclude.h>

namespace FalconEngine
{

enum class MouseButton
{
    LeftButton,
    RightButton,
    MiddleButton
};

enum class MouseButtonState
{
    Pressed,
    Released,
};

struct MouseState
{
    MouseState();

    double X;
    double Y;

    MouseButtonState LeftButton;
    MouseButtonState MiddleButton;
    MouseButtonState RightButton;
};

class Mouse : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Mouse();
    ~Mouse();

    void Update(float deltaTime);

    bool ButtonPressed(MouseButton button) const;
    bool ButtonReleased(MouseButton button)
    {
        return mWasReleased[button];
    }

    bool ButtonDoubleClicked(Button button)
    {
        return mWasDoubleClicked[button];
    }

    int GetRelativeX() const
    {
        return mouse_state.lX;
    }
    int GetRelativeY() const
    {
        return mouse_state.lY;
    }
    int GetRelativeZ() const
    {
        return mouse_state.lZ;
    }

    int GetAbsoluteX() const
    {
        return absolute_mouse_state.lX;
    }
    int GetAbsoluteY() const
    {
        return absolute_mouse_state.lY;
    }
    int GetAbsoluteZ() const
    {
        return absolute_mouse_state.lZ;
    }

    void GetAbsolutePosition(int& x, int& y, int& z);
    void GetRelativePosition(int& x, int& y, int& z);

    Vector2f GetPosition() const;
    Vector2f GetRelativePosition() const;

    int GetMouseWheelValue() const
    {
        return absolute_mouse_state.lZ;
    }

private:
    bool mWasPressed[8];
    bool mWasReleased[8];
    bool mWasDoubleClicked[8];
    float mLastReleaseTime[8];

    bool mBBuffered;

    void Initialize();
};

}
