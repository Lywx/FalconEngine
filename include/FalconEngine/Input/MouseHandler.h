#pragma once

#include <FalconEngine/Input/Header.h>

#include <memory>

#include <FalconEngine/Input/InputHandler.h>

namespace FalconEngine
{

class MouseState;
using MouseStateSharedPtr = std::shared_ptr<MouseState>;

class FALCON_ENGINE_ITEM_INPUT MouseHandler : public InputHandler<MouseStateSharedPtr>
{
public:
    MouseHandler();
};

}

