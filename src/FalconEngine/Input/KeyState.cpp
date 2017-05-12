#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
KeyState::KeyState() :
    mKey(Key::Unknown),
    mPressed(false),
    mUp(false),
    mDown(false)
{
}

KeyState::KeyState(Key key) :
    mKey(key),
    mPressed(false),
    mUp(false),
    mDown(false)
{
}
}
