#pragma once

namespace FalconEngine {
namespace Input {

enum eGamepadAxes
{
    JOY_AXIS_X,
    JOY_AXIS_Y,
    JOY_AXIS_Z,
    JOY_AXIS_X1,
    JOY_AXIS_Y1,
    JOY_AXIS_Z1,
    JOY_MAX_AXES,
};

enum eGamepadButtons
{
    JOY_BUTTON_00,
    JOY_BUTTON_01,
    JOY_BUTTON_02,
    JOY_BUTTON_03,
    JOY_BUTTON_04,
    JOY_BUTTON_05,
    JOY_BUTTON_06,
    JOY_BUTTON_07,
    JOY_BUTTON_08,
    JOY_BUTTON_09,
    JOY_BUTTON_10,
    JOY_BUTTON_11,
    JOY_BUTTON_12,
    JOY_BUTTON_13,
    JOY_BUTTON_14,
    JOY_BUTTON_15,
    JOY_BUTTON_16,
    JOY_BUTTON_17,
    JOY_BUTTON_18,
    JOY_BUTTON_19,
    JOY_BUTTON_20,
    JOY_BUTTON_21,
    JOY_BUTTON_22,
    JOY_BUTTON_23,
    JOY_MAX_BUTTONS
};

class Gamepad
{
    InputObject    *m_inputObject;
    InputDevice    *m_device;
    DIJOYSTATE2     m_gamepadState;

    size_t          m_ID;
    size_t          m_NumDevices;

    bool Initialize(InputObject *di, HWND hwnd, bool buffered = FALSE);
    void ClearDevice();

    InputDevice *GetDevice() const { return m_device; }

    friend class InputState;

public:

    Gamepad();
    ~Gamepad();

    void Update(float deltaTime);

    int GetAxis(eGamepadAxes axis);
    wchar_t GetButton(eGamepadButtons button);

    bool IsReady() const;

    static size_t CountDevices();
    BOOL CALLBACK EnumDeviceCallback(LPCDIDEVICEINSTANCEW instance, LPVOID context);

};

}
}
