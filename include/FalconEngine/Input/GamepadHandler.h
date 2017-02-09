#pragma once

#include "InputHandler.h"
namespace FalconEngine {


class gamepad_handler : public InputHandler
{
public:
    fnGamepadHandler mPHandler;
    gamepad_handler()
        : InputHandler()
        , mPHandler(0)
    {}
};

}
}
