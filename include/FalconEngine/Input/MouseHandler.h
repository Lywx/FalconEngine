#pragma once

#include <FalconEngine/InputInclude.h>

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

