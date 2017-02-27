#include <FalconEngine/Input/KeyboardHandler.h>

namespace FalconEngine
{

inline KeyboardHandler::KeyboardHandler() :
    InputHandler(InputPriority::System),
    mEnabled(true)
{
}

}
