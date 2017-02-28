#pragma once

#include <FalconEngine/Input/InputInclude.h>

#include <memory>

#include <FalconEngine/Input/InputHandler.h>
#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

class MouseHandler : public InputHandler<MouseStateSharedPtr>
{
public:
    MouseHandler();
};

}

