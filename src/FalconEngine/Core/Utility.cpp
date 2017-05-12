#include <FalconEngine/Core/Utility.h>

namespace FalconEngine
{

RuntimeException::RuntimeException(const std::string& message) :
    runtime_error(message)
{
    Debug::OutputString(message);
}

}
