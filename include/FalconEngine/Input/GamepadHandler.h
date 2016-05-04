#pragma once

#include "InputHandler.h"
namespace FalconEngine {


class gamepad_handler : public InputHandler
{
public:
    fnGamepadHandler m_pHandler;
    gamepad_handler()
        : InputHandler()
        , m_pHandler(0)
    {}
};

}
}
