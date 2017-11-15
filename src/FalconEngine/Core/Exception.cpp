#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

RuntimeException::RuntimeException(const std::string& message) :
    runtime_error(message)
{
    // TODO(Wuxiang): 2017-10-27 15:45 Read about exception in multi-threading.
    Debug::OutputString(message);
}

}
