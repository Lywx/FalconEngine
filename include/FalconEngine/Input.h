#pragma once

#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>

#include <vector>
#include <memory>
#include <chrono>

namespace FalconEngine {
namespace Input
{

class Keyboard;
class Mouse;
class Gamepad;

enum {
    IN_DEFAULT,
    IN_EXCLUSIVE,
};

typedef bool(*fnMouseHandler)(std::shared_ptr<Mouse> pMouse, void *userData);
typedef bool(*fnGamepadHandler)(std::shared_ptr<Gamepad> pgamepad, void *userData);

inline bool ComparePriority(InputHandler& a, InputHandler& b)
{
    if (a.m_priority < b.m_priority)
    {
        return false;
    }

    if (a.m_priority > b.m_priority)
    {
        return true;
    }

    return false;
}

}
}