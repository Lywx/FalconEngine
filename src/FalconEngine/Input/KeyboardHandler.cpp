#include <FalconEngine/Input/KeyboardHandler.h>

namespace FalconEngine
{

KeyboardHandler::KeyboardHandler() :
    InputHandler(InputPriority::System),
    mEnabled(true)
{
}

}
