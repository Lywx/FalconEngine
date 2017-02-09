#pragma once

#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine {

enum
{
    MOUSE_BUTTON_0,
    MOUSE_BUTTON_1,
    MOUSE_BUTTON_2,
    MOUSE_BUTTON_3,
    MOUSE_BUTTON_4,
    MOUSE_BUTTON_5,
    MOUSE_BUTTON_6,
    MOUSE_BUTTON_7,
    MAX_MOUSE_BUTTONS
};

class Mouse
{

public:

    Mouse();
    ~Mouse();

    enum Button
    {
        Left,
        Right,
        Middle
    };

    void Update(float deltaTime);

    bool ButtonPressed(Button button) const;
    bool ButtonReleased(Button button) { return mWasReleased[button]; }
    bool ButtonDoubleClicked(Button button) { return mWasDoubleClicked[button]; }

    int GetRelativeX() const { return mouse_state.lX; }
    int GetRelativeY() const { return mouse_state.lY; }
    int GetRelativeZ() const { return mouse_state.lZ; }

    int GetAbsoluteX() const { return absolute_mouse_state.lX; }
    int GetAbsoluteY() const { return absolute_mouse_state.lY; }
    int GetAbsoluteZ() const { return absolute_mouse_state.lZ; }

    void GetAbsolutePosition(int& x, int& y, int& z);
    void GetRelativePosition(int& x, int& y, int& z);

    Vector2f GetPosition() const;
    Vector2f GetRelativePosition() const;

    int GetMouseWheelValue() const { return absolute_mouse_state.lZ; }

private:

    InputDevice    *mDevice;
    HANDLE          mouse_event;
    DIMOUSESTATE2   mouse_state;
    DIMOUSESTATE2   absolute_mouse_state;
    HWND mHwnd;
    std::chrono::systemClock::time_point mLastUpdate;

    bool mWasPressed[8];
    bool mWasReleased[8];
    bool mWasDoubleClicked[8];
    float mLastReleaseTime[8];

    bool mBBuffered;

    bool Initialize(InputObject *di, HWND hwnd, bool buffered = FALSE);
    void ClearDevice();

    InputDevice *GetDevice() const { return mDevice; }

    friend class InputState;
};

}
