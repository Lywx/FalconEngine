#pragma once

#include <FalconEngine/Input/Common.h>

#include <unordered_map>

#include <FalconEngine/Input/MouseButton.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API MouseButtonPressState
{
    Pressed,
    Released,
};

enum class MouseButton;
class FALCON_ENGINE_API MouseButtonState final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    MouseButtonState();
    explicit MouseButtonState(MouseButton button);
    ~MouseButtonState() = default;

public:
    MouseButton mButton;
    bool        mButtonChanged = false;
    bool        mPressed;
    double      mPressedMoment = 0;   // Millisecond time stamp.
    bool        mDown;                // Transition from being released to being pressed.
    bool        mUp;                  // Transition from being pressed to being released.
};

#pragma warning(disable: 4251)
class FALCON_ENGINE_API MouseButtonStateMap : public std::unordered_map<MouseButton, MouseButtonState>
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    MouseButtonStateMap();
};
#pragma warning(default: 4251)

}
