#pragma once

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Mouse final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Mouse();
    ~Mouse();

private:
    MouseState mState;
};

}
