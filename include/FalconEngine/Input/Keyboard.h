#pragma once

#define BUFFER_SIZE (256)

namespace FalconEngine {


class Keyboard
{
    DIDEVICEOBJECTDATA didod[BUFFER_SIZE];

    char            key_state[256];
    char            old_key_state[256];

    bool            m_bBuffered;

    bool Initialize(bool buffered = false);

    friend class InputState;

public:

    Keyboard();
    ~Keyboard();

    void Update(float deltaTime);
    bool KeyDown(wchar_t key);
    bool KeyPressed(wchar_t key);
    bool KeyUp(wchar_t key);

    WCHAR GetKeyPress();
    const wchar_t *GetKeyDescription(wchar_t key);

    void Flush();
};

}