#pragma once

#include <FalconEngine/Input/InputInclude.h>

#include <memory>

#include <FalconEngine/Input/InputHandler.h>
#include <FalconEngine/Input/Keyboard.h>

namespace FalconEngine
{

class GameEngineInput;

class KeyboardHandler : public InputHandler<KeyboardSharedPtr>
{
    FALCON_ENGINE_RTTI_DECLARE;

    friend class GameEngineInput;

public:
    KeyboardHandler();
    virtual ~KeyboardHandler() = default;

    void
    Enable(bool enabled)
    {
        mEnabled = enabled;
    }

    bool
    Enabled() const
    {
        return mEnabled;
    }

private:
    bool mEnabled;
};

}
