#pragma once

#include "InputHandler.h"

namespace FalconEngine {


class MouseHandler : public InputHandler
{
public:
    fnMouseHandler m_pHandler;
    MouseHandler()
        : InputHandler()
        , m_pHandler(0)
    {}
};


}
}

