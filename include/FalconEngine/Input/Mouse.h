#pragma once

#include <FalconEngine/InputInclude.h>
#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

class Mouse final
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
