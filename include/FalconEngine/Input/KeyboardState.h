#pragma once

#include <FalconEngine/Core/Macro.h>

#include <unordered_map>

#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN KeyboardState final :
private std::unordered_map<Key, KeyState>
{
public:
    KeyboardState();

public:
    bool
    KeyPressed(Key key) const;

    bool
    KeyReleased(Key key) const;

    bool
    KeyDown(Key key) const;

    bool
    KeyUp(Key key) const;

// internal
public:
    // @param time -- Millisecond time stamp.
    void
    SetKeyInternal(Key key, bool keyPressed, double timeCurrent);

    // @param elpased -- Millisecond duration between last and this update.
    void
    UpdateEvent(double elapsed);

private:
    void
    UpdateKey(KeyState & keyState,
              bool      keyPressedCurrent,
              bool      keyPressedPrevious,
              double    timeCurrent);
};
FALCON_ENGINE_CLASS_END

}
