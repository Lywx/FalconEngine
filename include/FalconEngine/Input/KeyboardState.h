#pragma once

#include <FalconEngine/InputInclude.h>

#include <unordered_map>

#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

class KeyboardState final : private std::unordered_map<Key, KeyState>
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

// internal
public:
    // @param time -- Millisecond time stamp.
    void
    SetKeyInternal(Key key, bool pressed, double time);
};

}
