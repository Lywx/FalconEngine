#pragma once

#include <FalconEngine/Input/Common.h>

#if defined (FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Platform/GLFW/GLFWKey.h>
#elif defined (FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Platform/Win32/Win32Key.h>
#endif

namespace FalconEngine
{

using KeyHash = std::hash<int>;

class FALCON_ENGINE_API KeyState final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    KeyState();
    explicit KeyState(Key key);
    ~KeyState() = default;

public:
    Key    mKey;
    bool   mKeyChanged = false;
    bool   mPressed;
    double mPressedMoment = 0;   // Millisecond time stamp.
    bool   mUp;                  // Transition from being pressed to being released.
    bool   mDown;                // Transition from being released to being pressed.
};

}

namespace std
{

template <>
struct hash<FalconEngine::Key>
{
    size_t
    operator()(const FalconEngine::Key& key) const
    {
        return FalconEngine::KeyHash {} (int(key));
    }
};

}
