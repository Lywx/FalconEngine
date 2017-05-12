#pragma once

#include <FalconEngine/Input/Header.h>
#include <FalconEngine/Input/MouseState.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_INPUT Mouse final
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
