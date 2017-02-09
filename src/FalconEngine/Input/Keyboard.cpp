#include <FalconEngine/Input/Keyboard.h>

namespace FalconEngine {
namespace Input {

bool Keyboard::Initialize(bool buffered)
{
    HRESULT hr = S_OK;

    hr = di->CreateDevice(GUID_SysKeyboard, &mDevice, nullptr);
    if (FAILED(hr))
    {
        return false;
    }

    hr = mDevice->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hr))
    {
        return false;
    }

    DWORD dwCoopFlags = 0;
    dwCoopFlags |= DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY;

    hr = mDevice->SetCooperativeLevel(hwnd, dwCoopFlags);
    if (FAILED(hr))
    {
        return false;
    }

    if (buffered)
    {
        mBBuffered = buffered;

        DIPROPDWORD dipdw;

        dipdw.diph.dwSize = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        dipdw.diph.dwObj = 0;
        dipdw.diph.dwHow = DIPH_DEVICE;
        dipdw.dwData = BUFFER_SIZE;

        if (FAILED(hr = mDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
        {
            return false;
        }
    }

    hr = mDevice->Acquire();
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

}
}
