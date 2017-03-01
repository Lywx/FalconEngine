#pragma once

#include <FalconEngine/InputInclude.h>
#include <FalconEngine/Input/InputHandler.h>

namespace FalconEngine
{

class KeyboardState;
using KeyboardStateSharedPtr = std::shared_ptr<KeyboardState>;

class KeyboardHandler : public InputHandler<KeyboardStateSharedPtr>
{
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
