#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>

#include <FalconEngine/Input/InputHandler.h>

namespace FalconEngine
{

class MouseState;
using MouseStateSharedPtr = std::shared_ptr<MouseState>;

class MouseHandler : public InputHandler<MouseStateSharedPtr>
{
public:
    MouseHandler();
};

}

