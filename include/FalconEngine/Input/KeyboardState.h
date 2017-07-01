#pragma once

#include <FalconEngine/Input/Common.h>

#include <unordered_map>

#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API KeyboardState final : private std::unordered_map<Key, KeyState>
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
#pragma warning(default: 4251)

}
