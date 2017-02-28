#include <FalconEngine/Input/KeyState.h>

namespace FalconEngine
{

KeyState::KeyState(Key key) :
    mKey(key),
    mPressed(false),
    mUp(false),
    mDown(false)
{
}
}
