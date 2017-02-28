#pragma once

#include <FalconEngine/Input/InputInclude.h>

#include <unordered_map>

#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

class KeyboardState sealed : private std::unordered_map<Key, KeyState>
{
public:
    KeyboardState();

public:
    bool
    KeyPressed(Key key) const;

    bool
    KeyDown(Key key) const;

    bool
    KeyUp(Key key) const;

    // @param time -- Millisecond time stamp.
    void
    KeySetState(Key key, bool pressed, double time);
};

using KeyboardStateSharedPtr = std::shared_ptr<KeyboardState>;

}
