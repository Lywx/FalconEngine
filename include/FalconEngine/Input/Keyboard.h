#pragma once

#include <FalconEngine/Input/InputInclude.h>

namespace FalconEngine
{

class Keyboard : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Keyboard();
    virtual ~Keyboard();

    char key_state[256];
    char old_key_state[256];

    bool Initialize(bool buffered = false);

    void
    Update(float deltaTime);

    bool
    KeyDown(char key);

    bool
    KeyPressed(char key);

    bool
    KeyUp(char key);

    char
    GetKeyPress();

    const char *
    GetKeyDescription(wchar_t key);

    void Flush();
};

using KeyboardSharedPtr = std::shared_ptr<Keyboard>;
}