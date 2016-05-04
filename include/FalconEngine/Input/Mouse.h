#pragma once

#include <FalconEngine/Math/Vector2f.h>

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
    bool ButtonReleased(Button button) { return m_wasReleased[button]; }
    bool ButtonDoubleClicked(Button button) { return m_wasDoubleClicked[button]; }

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

    InputDevice    *m_device;
    HANDLE          mouse_event;
    DIMOUSESTATE2   mouse_state;
    DIMOUSESTATE2   absolute_mouse_state;
    HWND m_hwnd;
    std::chrono::system_clock::time_point m_lastUpdate;

    bool m_wasPressed[8];
    bool m_wasReleased[8];
    bool m_wasDoubleClicked[8];
    float m_lastReleaseTime[8];

    bool m_bBuffered;

    bool Initialize(InputObject *di, HWND hwnd, bool buffered = FALSE);
    void ClearDevice();

    InputDevice *GetDevice() const { return m_device; }

    friend class InputState;
};

}
