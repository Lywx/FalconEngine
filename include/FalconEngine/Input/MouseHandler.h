#pragma once

#include <FalconEngine/Input/InputInclude.h>

#include <memory>

#include <FalconEngine/Input/InputHandler.h>

namespace FalconEngine
{

typedef bool(*MouseHandlerPrototype)(std::shared_ptr<Mouse> mouse, void *userData);

class MouseHandler : public InputHandler
{
public:
    MouseHandlerPrototype mPHandler;
    MouseHandler()
        : InputHandler()
        , mPHandler(0)
    {}
};

}

