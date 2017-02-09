#pragma once

#include "InputHandler.h"

namespace FalconEngine {


class MouseHandler : public InputHandler
{
public:
    fnMouseHandler mPHandler;
    MouseHandler()
        : InputHandler()
        , mPHandler(0)
    {}
};


}
}

